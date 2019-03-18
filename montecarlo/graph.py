import plotly
import plotly.graph_objs as go

def readIn(filename):


	data = []
	newList = []
	file = open(filename, "r")
	for line in file:
		if line == "\n":
			data.append(newList)
			newList = []
		else:
			toappend = [int(i) for i in line.split(', ')[:len(line.split(', '))-1]]
			toappend.sort()
			newList.append(toappend)

	

	xlength = len(data[0][0])

	return data, xlength


def minmax(data):

	newdata = []
	for group in data:
		newList = []
		for strat in group:
			#print(strat)
			i = 0
			uniques = []
			values = []
			while i < len(strat):
				if i == 0:
					values.append(strat[i])
				index = i
				while index < len(strat) and strat[i] == strat[index]:
					index += 1
				uniques.append(index/len(strat))
				u
				if index < len(strat):
					values.append(strat[index])
				i = index
			#print(len(uniques),len(values))
			newList.append([uniques,values])
		newdata.append(newList)
	print(newdata[0][0])
		
	return newdata


def graph(newdata, xlength):

	plotly.tools.set_credentials_file(username='totorotoby', api_key='eCLf47JgEEHAtZV225i6')
	#print(data)
	traces = []
	count = 0
	for group in data:
		#count += 1
		for sample in group:
			top = sample[0]
			bottom = top[:len(top)-1]
			bottom.insert(0,0)
			x = sample[1]
			trace0 = go.Scatter(x=x, y=top, name='test', mode="lines")
			trace1 = go.Scatter(x=x, y=bottom, name='test', mode="lines")
	traces.append(trace)

	url = plotly.plotly.plot(traces)

def main():

	filename = "graph.dat"
	data, xlength = readIn(filename)
	newdata = minmax(data)
	graph(newdata, xlength)

main()