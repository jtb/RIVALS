print("Testing RIVALS\n")

sample1 = importBED("../Data/test.bed", "Output/bed_sample")
chr1 = "chr1"

version, num_elements = file_summary(sample1)
chrom_size, start, stop = chrom_summary(sample1, chr1)

print("\nversion: " .. version)
print("Number of intervals: " .. num_elements)
print("Chromosome " .. chr1 .. " of sample " .. sample1 .. " has " .. chrom_size .. " intervals, ranging from " .. start .. " (inclusive) to " .. stop .. " (exclusive)\n")


-- Count all intervals in sample1 that overlap chr8:28510032-31173640
C = count(range(sample1, "chr8", 28510032, 31173640))
print("\nNumber of intervals that overlap chr8:28510032-31173640:", C)
print("")
