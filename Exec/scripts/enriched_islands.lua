print("Count the number of islands that have a maximum coverage of at least 2.\n")

sample1 = importBED("../Data/test.bed", "Output/bed_sample")

islands = flatten(range(sample1))
coverage2 = clique(range(sample1), 2)

print("Number of islands with maximum coverage of at least 2 is", count(contains(islands, coverage2)))
