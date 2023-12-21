library(igraph)
net <- graph.famous("Zachary")
pal2 <- rainbow(5, alpha=.5)
#main graph view
plot(net, vertex.color=pal2, main="Karate Club Graph")