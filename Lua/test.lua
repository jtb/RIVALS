rivals1 = "bed_test"
--rivals2 = "gff_test"
importBED("../Demo/Data/test.bed", rivals1)
--importGFF("../Demo/Data/chrX.gff", rivals2)
--saveAsBED("gff.bed", range(rivals2))
--saveAsBED(merge(range(rivals2), range(rivals2)))
--saveAsBED(interval("chr1", 100, 200))
--saveAsBED(merge(interval("chr1",100,200), interval("chr1", 50, 150)))

-- saveAsBED(range(rival1, chr8, 28510032, 31173640))
saveAsBED(range(rivals1))

-- A = "aloho"
-- add(add(A, "pho"), "go")
