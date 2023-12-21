library(igraph)
net <- erdos.renyi.game(150, 1000, type = "gnm")
plot(net, vertex.color=pal2, main="Random Graph")
