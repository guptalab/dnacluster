#Girvan Newman
ceb <- cluster_edge_betweenness(net) 

#Community plot
plot(ceb, net, main="Girvan-Newman Algorithm")

#modularity
modularity(ceb)

#no
length(ceb)