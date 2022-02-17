import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import scipy.sparse as sp
import time
from threading import Thread

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

matrix = np.genfromtxt("matrix.txt", delimiter=' ')
edags = get_matrix_triad(matrix)
G = nx.Graph()
H = nx.path_graph(matrix.shape[0]) 
G.add_nodes_from(H)
G.add_weighted_edges_from(edags)
colors = np.arange(matrix.shape[0])

def PrintMatrix():   
    nx.draw(G,pos=nx.spring_layout(G),node_color="black")
    plt.show()

def ReadFile(name):
    name = "command.txt"
    while True:
        f = open(name, 'r')        
        if f.readline() == "new":
            f.close()
            th_paint.start()
        f.close()
        time.sleep(5)


def PaintGraph(name):    
    f = open(name, 'r')    
    if f.readline() == "new":
        if  f.readline() == "DepthFirstSearch":       
            nx.draw(G,pos=nx.spring_layout(G),node_color="red")
        elif f.readline() == "BreadthFirstSearch":   
            nx.draw(G,pos=nx.spring_layout(G),node_color="green")
        elif f.readline() == "PrimsAlgorithm":   
            nx.draw(G,pos=nx.spring_layout(G),node_color="blue")
        elif f.readline() == "DijkstraAlgorithm":   
            nx.draw(G,pos=nx.spring_layout(G),node_color="yellow")
        plt.show()
        f.close()
        fw = open(name, 'w')
        fw.write('painted')
    
s = "c"
th_matrix = Thread(target=PrintMatrix)
th_read = Thread(target=ReadFile, args=(s))
th_paint = Thread(target=PaintGraph, args=(s))
th_matrix.start()
th_read.start()


