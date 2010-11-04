-- Import bed and gff files into Rival samples
importBED("../Demo/Data/test.bed", "bed_sample")
importGFF("../Demo/Data/chrX.gff", "gff_sample")

-- Save gff_sample to a BED file called gff.bed
g = "gff_sample"
saveAsBED("gff.bed", range(g))

-- Merge two intervals, write to a rival file, then read file to standard out
saveAsRival("sample3", merge(interval("chr1",100,200), interval("chr1", 50, 150)))
saveAsBED(range("sample3"))
print("Number of intervals in sample3 is ", count(range("sample3")))

-- Print out all intervals in bed_sample that overlap chr8:28510032-31173640
saveAsBED(range("bed_sample", "chr8", 28510032, 31173640))

