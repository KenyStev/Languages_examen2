sum_res = 45

table =[[7,4,1,6,9,8,3,2,5],
		[5,3,8,2,4,1,6,7,9],
		[9,2,6,3,7,5,4,1,8],
		[4,0,0,0,0,0,0,0,0],
		[2,0,0,0,0,0,0,0,0],
		[8,0,0,0,0,0,0,0,0],
		[1,0,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0,0,0],
		[0,0,0,0,0,0,0,0,0]]

def checkSumBox(box,fila,col):
	suma = 0
	for x in range(0,9):
		suma += x

	return suma == sum_res

def checkSumCol(table):
	for x in range(0,9):