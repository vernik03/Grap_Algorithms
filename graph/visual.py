from matplotlib import font_manager
import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import scipy.sparse as sp
import time
from threading import Thread
import matplotlib.animation as animation
import warnings
warnings.filterwarnings("ignore")



def get_matrix_triad(coo_matrix , data=False):
	'''
		Получить кортежное представление матрицы (строка, столбец)
		 Когда данные истинны (строка, столбец, данные)
	:dependent  scipy
	 : param coo_matrix: Тип разреженной матрицы, представленной троек, может быть numpy.ndarray
	 : param data: вам нужно значение данных
	:return:
		list
	'''
	# Тип проверки
	if not sp.isspmatrix_coo(coo_matrix):
		# Преобразуется в разреженную матрицу, представленную троек
		coo_matrix = sp.coo_matrix(coo_matrix)
	# nx3   matrix Столбцы представляют собой строки матрицы, столбцы матрицы и соответствующие значения матрицы.
	temp = np.vstack((coo_matrix.row , coo_matrix.col , coo_matrix.data)).transpose()
	return temp.tolist()

def PrintMatrix():   
    fig = plt.figure()
    net = fig.add_subplot(111)
    global x
    pos=nx.spring_layout(G)
    #pos=nx.graphviz_layout(G)
    def animate(i):
        plt.clf()
        plt.cla()
        colors = nx.get_edge_attributes(G,'color').values()
        weights = nx.get_edge_attributes(G,'weight').values()
        if x == 1:
            nx.draw(G, pos, edge_color=colors, node_color = color_map, width=list(weights),  labels=labeldict, with_labels=True, font_color='white')
        elif x == 2:
            nx.draw(G,pos=pos,node_color="green")
        elif x == 3:
            nx.draw(G,pos=pos,node_color="blue")
        elif x == 4:
            nx.draw(G,pos=pos,node_color="blue")
        elif x == 5:
            nx.draw(G, pos, edge_color=colors, node_color = color_map, width=list(weights),  labels=labeldict, with_labels=True, font_color='white')
        elif x == 6:
            nx.draw(G,pos=pos,node_color="blue")
        elif x == 7:
            nx.draw(G,pos=pos,node_color="blue")
        elif x == 8:
            nx.draw(G,pos=pos,node_color="blue")
        else:
            nx.draw(G,pos=pos,node_color="black")  

    ani = animation.FuncAnimation(fig, animate, interval=1000)
    plt.show()
    

def ReadFile(name):     
    global x
    while True:
        f = open(name, 'r')
        str = f.readline()
        if str == "new\n":
            f.close()
            PaintGraph(name)
        f.close()
        time.sleep(1)


def PaintGraph(name): 
    global x
    f = open(name, 'r')    
    str = f.readline()
    if str == "new\n":       
        str = f.readline()
        lst = f.readline()
        lst = list(map(int, lst.split()))
        if  str == "DepthFirstSearch\n":       
            x = 1
            i = 0
            while i < len(lst)-1:
                G.add_edge(lst[i],lst[i+1],color='r',weight=2)
                for node in G:                    
                    if node == lst[i] or node == lst[i+1]:
                        color_map[node]='red' 
                i += 2 
        elif str == "BreadthFirstSearch\n":   
            x = 2
        elif str == "Prims\n":   
            x = 3
        elif str == "Dijkstra\n":   
            x = 4
        elif str == "AStar\n":   
            x = 5
            i = 0
            while i < len(lst)-1:
                G.add_edge(lst[i],lst[i+1],color='r',weight=2)
                for node in G:                    
                    if node == lst[i] or node == lst[i+1]:
                        color_map[node]='red' 
                i += 1 
        elif str == "FordFulkerston\n":   
            x = 6
        elif str == "DijkstraBidirectional\n":   
            x = 7
        elif str == "AStarBidirectional\n":   
            x = 8
        f.close()
        fw = open(name, 'w')
        fw.write('painted')



matrix = np.genfromtxt("matrix.txt", delimiter=' ')
edges = get_matrix_triad(matrix)
G = nx.Graph()
H = nx.path_graph(matrix.shape[0]) 
G.add_nodes_from(H)
G.add_weighted_edges_from(edges)
colors = np.arange(matrix.shape[0])
for e in G.edges():
    G[e[0]][e[1]]['color'] = 'black'
color_map = []
labeldict = {}
for node in G:
    color_map.append('black')       
    labeldict[node] = node+1
 


x = 0
s = "command.txt"
th_matrix = Thread(target=PrintMatrix, daemon=True)
th_read = Thread(target=ReadFile, args=(s,))
th_matrix.start()
th_read.start()

