#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "rivals.h"

static int colors[][3] = {
  {0xFF, 0xED, 0x99},
  {0xFF, 0xE4, 0x66},
  {0xB8, 0xC4, 0x92},
  {0x9A, 0xA7, 0xC6},
  {0xEB, 0xB9, 0x6B},
  {0xDB, 0x90, 0x5C},
};

static rivals::Domain left_end; //left-most end point of all samples
static rivals::Domain right_end;//right-most end point of all samples

static rivals::Domain start; // current start
static rivals::Domain stop; // current stop
static std::string chr; // name of chromosome
static std::vector<std::string> samples; //list of samples

static GLsizei g_w, g_h; // width and height of window

//zoom: zoom the view by a factor of z
void zoom(double z){
  if(stop < start){
    std::swap(start, stop);
  }
  double denom = 2.0*z;
  
  double num = (z+1)*start + (z-1)*stop;
  if(num/denom < 1.0*left_end){
    start = left_end;
  }else{
    start = num/denom;
  }

  num = (z-1)*start + (z+1)*stop;
  if(num/denom > 1.0*right_end){
    stop = right_end;
  }else{
    stop = num/denom;
  }
}
//shift: shift view by s*L, where L is the logical width of the window
//s=0 means no shift. s=1 means shift by entire window size 
void shift(double s){
  if(stop < start){
    std::swap(start, stop);
  }
  size_t N = ((stop-start) < g_w)? (stop-start) : g_w;
  size_t dx = std::ceil(1.0*(stop-start)/N);

  //if start is an unsigned int, make sure our arithmitic doesn't lead to negative starts
  if(s < 0){
    if(start < left_end - dx*(N*s)){//-dx*N*s will be positive
      start = left_end;
    }else{
      start = start + dx*(N*s);
    }
    stop = start + dx*N;
  }else{
    //shift right as long as we don't go off right edge
    if(rivals::Domain(start + dx*N) <= right_end){
      start = start + dx*(N*s);
      stop = start + dx*N;
    }
  }
}

void processSpecialKeys(int key, int x, int y) {
  switch(key) {
  case GLUT_KEY_UP : 
    zoom(2.0);
    break;
  case GLUT_KEY_DOWN:
    zoom(0.5);
    break;
  case GLUT_KEY_LEFT:
    shift(-1.0/16);
    break;
  case GLUT_KEY_RIGHT:
    shift(1.0/16);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

int plotCoverage(std::vector<int> & cov, size_t dx, std::string & sample){
  assert(cov.size());
  //std::cout << sample << "\t" << chr << "\t" << start << "\t" << stop << std::endl;
  //std::cout << "gw is " << g_w << " and gh is " << g_h << std::endl;
  std::auto_ptr<rivals::Node> samp = rivals::range(sample, chr, start, stop);
  rivals::Interval c;
  samp->iter->setChr(chr);
  while(samp->iter->next(chr, c)){
    if(c.getStart() < start){
      cov.at(0)++;
    }else{
      cov.at( (c.getStart()-start)/dx )++;
    }
    if(c.getStop() < stop){
      size_t index = 1+ (c.getStop() - start)/dx;
      if(index < cov.size()){
	cov.at(index)--;
      }
    }
  }

  int sum = 0;
  int height = 0;
  for(size_t i = 0; i < cov.size(); i++){
    sum += cov.at(i);
    if(sum > height) height = sum;
  }
  return (height+1);//in case height = 0
}

// Function plotting func
void draw(std::string & sample){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if(stop < start){
    std::swap(start, stop);
  }
  size_t N = ((stop-start) < g_w)? (stop-start) : g_w;
  size_t dx = std::ceil(1.0*(stop-start)/N);
  
  std::vector<int> histo(N , 0);
  int height = plotCoverage(histo, dx, sample);
  
  glPushMatrix(); //GL_MODELVIEW is default
  glScalef(1.0/(stop-start), 1.0/height, 1.0);
  glTranslatef(-1.0*start, 0.0, 0.0);
  
  double pos = start;
  double sum = 0;
  for(size_t i = 0; i < histo.size(); i++){
    sum += histo.at(i);
    double posOld = pos;
    pos = ( (pos+dx) < stop) ? pos+dx : stop;

    glBegin(GL_QUADS);
    glVertex2f(posOld, sum);
    glVertex2f(pos, sum);
    glVertex2f(pos, 0.0);
    glVertex2f(posOld, 0.0);
    glEnd();
  }
}

/* Redrawing func */
void redraw(void)
{
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  size_t N = samples.size();
  for(size_t i = 0; i < N; i++){
    glViewport(0, i*g_h/N, g_w, g_h/N);
    glColor3f((1.0/255)*colors[i%6][0], (1.0/255)*colors[i%6][1], (1.0/255)*colors[i%6][2]); 
    draw(samples.at(i));
  }

  glutSwapBuffers();
}

/* Key press processing */
void key(unsigned char c, int x, int y)
{
  if(c == 27) exit(0);//esc will exit the program
  if(c == 72 || c == 104){//h or H will go to fully zoomed out view (home)
    start = left_end;
    stop = right_end;
    glutPostRedisplay();
  }
}

/* Window reashape */
void reshape(int w, int h)
{
  g_w = w;
  g_h = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
}

//Find the min and max coords of the samples, and set that to home view
void initCoords(){
  assert(samples.size());
  rivals::chr_summary(samples.at(0), chr, left_end, right_end);
  for(size_t i = 1; i < samples.size(); i++){
    rivals::chr_summary(samples.at(i), chr, start, stop);
    if(start < left_end) left_end = start;
    if(stop > right_end) right_end = stop;
  }

  start = left_end;
  stop = right_end;
}

/* Main function */
int main(int argc, char **argv)
{
  if(argc < 3){
    std::cout << "Usage: ./plot chromosome Rival_1 <... Rival_N>" << std::endl;
    exit(0);
  }

  chr = argv[1];
  for(int i = 2; i < argc; i++){
    samples.push_back(argv[i]);
  }

  initCoords();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);

  glutCreateWindow("RIVALS Viewer");

  /* Register GLUT callbacks. */
  glutDisplayFunc(redraw);
  glutKeyboardFunc(key);
  glutReshapeFunc(reshape);
  glutSpecialFunc(processSpecialKeys);

  /* Init the GL state */
  glLineWidth(1.0);
  
  /* Main loop */
  glutMainLoop();

  return 0;
}
