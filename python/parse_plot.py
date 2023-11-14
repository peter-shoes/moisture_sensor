import matplotlib.plt as plt

def parse(file):
	a0 = []
	a1 = []
	a2 = []
	with f as open(file, 'r'):
		l = f.readlines()
		for line in l:
			line = line.split(":")
			dat = line[1].split(" ")
			if line[0] = "A0":
				for d in dat:
					a0.append(int(d))
			#etc ...
	return [a0,a1,a2]
	
	
def main():
	data = parse("get the file from args")
	
	#do plotting (ask chatgpt)
	
if __name__ == "__main__":
	main()
