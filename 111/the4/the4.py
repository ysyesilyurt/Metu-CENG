def query(decision_tree, variable_value):

	def finder(variable,variable_value):
		if type(variable) == str:
			for x in variable_value:
				if x[0] == variable:
					value = x[1]
					break
				else:
					if x==variable_value[-1]:
						return variable
					else:
						continue
			return value
		else:
			return variable

	def checker(lst):
		if lst[0]=="==":
			if finder(lst[1], variable_value) == finder(lst[2], variable_value):
				return True
			else:
				return False
		elif lst[0] == "!=":
			if finder(lst[1], variable_value) != finder(lst[2], variable_value):
				return True
			else:
				return False
		elif lst[0] == "<":
			if finder(lst[1], variable_value) < finder(lst[2], variable_value):
				return True
			else:
				return False
		elif lst[0] == ">":
			if finder(lst[1], variable_value) > finder(lst[2], variable_value):
				return True
			else:
				return False
		elif lst[0] == "in":
			if finder(lst[1], variable_value) in finder(lst[2], variable_value):
				return True
			else:
				return False
		elif lst[0] == "and":
			for i in range(1,len(lst)):
				if checker(lst[i]) == False :
					return False
			else:
				return True
		elif lst[0] == "or":
			for i in range(1,len(lst)):
				if checker(lst[i]) == True :
					return True
			else:
				return False
		elif lst[0] == "not":
			if checker(lst[1]) == True:
				return False
			else:
				return True

	def isleaf(lstt):
		if len(lstt) == 1:
			return True
		else:
			return False

	if isleaf(decision_tree[0]):
		return decision_tree
	else:
		if checker(decision_tree[0]) == True:
			return query(decision_tree[1], variable_value)
		else:
			return query(decision_tree[2], variable_value)
