nrsf = "nrsf"
chr1 = "chr1"
version, num_elements = file_summary(nrsf)
chrom_size, start, stop = chrom_summary(nrsf, chr1)

print("version: " .. version)
print("Number of intervals: " .. num_elements)
print("Chromosome " .. chr1 .. " of sample " .. nrsf .. " has " .. chrom_size .. " intervals, ranging from " .. start .. " (inclusive) to " .. stop .. " (exclusive)")
