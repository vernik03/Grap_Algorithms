from matplotlib import font_manager
import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import scipy.sparse as sp
import time
from threading import Thread
import matplotlib.animation as animation
import warnings
import sys
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
        nx.draw(G, pos, edge_color=colors, node_color = color_map, width=list(weights),  labels=labeldict, with_labels=True, font_color='white')

    ani = animation.FuncAnimation(fig, animate, interval=1000)
    plt.show()

def Repaint():
    color_map.clear()
    for node in G:
        color_map.append('black')   
    for e in G.edges():
        G[e[0]][e[1]]['color'] = 'black'
        G[e[0]][e[1]]['weight'] = 1
 

def ReadFile(name):     
    global x
    while True:
        f = open(name, 'r')
        str = f.readline()
        if str == "new\n":
            f.close()
            PaintGraph(name)
        elif str == "end\n":
            f.close()
            sys.exit()
        elif str == "clear\n":
            f.close()
            Repaint()
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
        if str == "Dijkstra\n": 
            Repaint() 
        else :  
            Repaint()
            i = 0
            while i < len(lst)-1:
                G[lst[i]][lst[i+1]]['color'] = 'red'
                G[lst[i]][lst[i+1]]['weight'] = 2
                for node in G:                    
                    if node == lst[i] or node == lst[i+1]:
                        color_map[node]='red' 
                i += 2 
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