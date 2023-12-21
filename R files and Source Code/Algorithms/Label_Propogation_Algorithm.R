#Label Propagation 
lp <- cluster_label_prop(net)

#Community plot
plot(lp, net, main="Label Propagation Algorithm")

#Modularity
modularity(lp)

#no
length(lp)