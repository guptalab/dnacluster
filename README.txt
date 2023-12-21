Problem Statement :- We are given N Reads(strings) S = {y1,y2,...,yN}, Our main aim is to "Partition this set", such that metric threshold between any two elements within a set in <= K. We are supposed to give the best partition which approximately matches with the actual Partition (As there are limitless partitions possible).

	Mathematically :- 
		1) Given N strings set S = {y1,y2,...,yN}.
		2) Find set of clusters(sets of string) C = {c1,c2,...,cn} where n is unknown, such that each yi (1<=i<=N) belongs to some cj (where 1<=j<=n).
		3) And for every str1,str2 belongs to cj (1<=j<=n), Edit distance between (str1,str2) <= K.



Solution Procedure :- 
	1) First we will find all the pairs of strings which have Edit didstance <=K.
		How ??
		
		--> Using Poucet Search Technique.
		--> First we will store all the Reads in a Trie T. And Root Rs.		(Time Complexity :- N*(average size of a string)).
		--> After that for each string we will use Poucet Search Technique.
			----------We will elaborate this technique more in documentation----------
		--> And thus we will get all the "Relevent Pairs".
	
	2) Now from all the pairs we got we treat it as *edges*,
		And all the Reads as *Nodes*, and thus we will make a *Graph*.
		
	3) Converting the problem statement :
		Now we need to find the "Community Detection in Social Networks".
		
	4) So for that we have different "Community Detection" techniques which we can apply and check which one is more convinient.
		--> Also we can modify one of the techniques for more optimized output.
		
		--> Community Detection Techniques 
			--> Girvan-Newman Algorithm
			--> Label Propagation Algorithm
			--> Fast Greedy Algorithm
			--> Spinglass Algorithm
			--> Walktrap Algorithm
			--> Louvain Algorithm
			--> Infomap Algorithm
			--> Leading Eigenvector Algorithm
		
		--> We need to take care about 1 more thing which is the clusters must be a extracted clique from the graph.
		
		***We can put a prefered range of modularity.
		***Other modification to Try :- (We can use a weighted graph :- edge weight inversely propostional to Edit distance).