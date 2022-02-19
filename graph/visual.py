import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import scipy.sparse as sp
import time
from threading import Thread
import matplotlib.animation as animation



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
        if x == 1:
            nx.draw(G,pos=pos,node_color="red")
        elif x == 2:
            nx.draw(G,pos=pos,node_color="green")
        elif x == 3:
            nx.draw(G,pos=pos,node_color="blue")
        elif x == 4:
            nx.draw(G,pos=pos,node_color="yellow")  
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
            print('!')
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
        print(str)
        if  str == "DepthFirstSearch\n":       
            x = 1
        elif str == "BreadthFirstSearch\n":   
            x = 2
        elif str == "PrimsAlgorithm\n":   
            x = 3
        elif str == "DijkstraAlgorithm\n":   
            x = 4
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

x = 0
s = "command.txt"
th_matrix = Thread(target=PrintMatrix, daemon=True)
th_read = Thread(target=ReadFile, args=(s,))
th_matrix.start()
th_read.start()






