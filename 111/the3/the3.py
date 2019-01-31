import sys
sys.setrecursionlimit(999999999)
import collections
import operator
import random
def hyphenate(word):
    word = list(word)
    if len(word) == 0:
        return []
    elif isvowel(word[0]):
        if len(word) == 1:
            return word
        elif isvowel(word[1]):
            return [word[0]] + hyphenate(word[1:])
        else:
            if len(word) == 2:
                word = "".join(word)
                return [word]
            elif isvowel(word[2]):
                return [word[0]] + hyphenate(word[1:])
            else:
                if len(word) == 3:
                    word = "".join(word)
                    return [word]
                elif isvowel(word[3]):
                    a = str(word[0] + word[1])
                    return [a] + hyphenate(word[2:])
                else:
                    if len(word) == 4:
                        word = "".join(word)
                        return [word]
                    elif isvowel(word[4]):
                        a = str(word[0] + word[1] + word[2])
                        return [a] + hyphenate(word[3:])
                    else:
                        if len(word) == 5:
                            word = "".join(word)
                            return [word]
                        elif isvowel(word[5]):
                            a = str(word[0] + word[1] + word[2] + word[3])
                            return [a] + hyphenate(word[4:])
                        word = "".join(word)
                        return [word]
    else:
        if len(word) == 1:
            return [word]
        elif isvowel(word[1]):
            if len(word) == 2:
                word = "".join(word)
                return [word]
            elif isvowel(word[2]):
                a = str(word[0] + word[1])
                return [a] + hyphenate(word[2:])
            else:
                if len(word) == 3:
                    word = "".join(word)
                    return [word]
                elif isvowel(word[3]):
                    a = str(word[0] + word[1])
                    return [a] + hyphenate(word[2:])
                else:
                    if len(word) == 4:
                        word = "".join(word)
                        return [word]
                    elif isvowel(word[4]):
                        a = str(word[0] + word[1] + word[2])
                        return [a] + hyphenate(word[3:])
                    else:
                        if len(word) == 5:
                            word = "".join(word)
                            return [word]
                        elif isvowel(word[5]):
                            a = str(word[0] + word[1] + word[2] + word[3])
                            return [a] + hyphenate(word[4:])
                        else:
                            if len(word) == 6:
                                word = "".join(word)
                                return [word]
                            elif isvowel(word[6]):
                                a = str(word[0] + word[1] + word[2] + word[3] + word[4])
                                return [a] + hyphenate(word[5:])
                            else:
                                word = "".join(word)
                                return [word]
        else:
            if len(word) == 2:
                return [word]
            elif isvowel(word[2]):
                if len(word) == 3:
                    word = "".join(word)
                    return [word]
                elif isvowel(word[3]):
                    a = str(word[0] + word[1])
                    return [a] + hyphenate(word[2:])
                else:
                    if len(word) == 4:
                        word = "".join(word)
                        return [word]
                    elif isvowel(word[4]):
                        a = str(word[0] + word[1] + word[2])
                        return [a] + hyphenate(word[3:])
                    else:
                        if len(word) == 5:
                            word = "".join(word)
                            return [word]
                        elif isvowel(word[5]):
                            a = str(word[0] + word[1] + word[2] + word[3])
                            return [a] + hyphenate(word[4:])
                        else:
                            if len(word) == 6:
                                word = "".join(word)
                                return [word]
                            elif isvowel(word[6]):
                                a = str(word[0] + word[1] + word[2] + word[3] + word[4])
                                return [a] + hyphenate(word[5:])
                            else:
                                if len(word) == 7:
                                    word = "".join(word)
                                    return [word]
                                elif isvowel(word[7]):
                                    a = str(word[0] + word[1] + word[2] + word[3] + word[4] + word[5])
                                    return [a] + hyphenate(word[6:])
                                else:
                                    word = "".join(word)
                                    return [word]
            else:
                if len(word) == 3:
                    return [word]
                elif isvowel(word[3]):
                    if len(word) == 4:
                        word = "".join(word)
                        return [word]
                    elif isvowel(word[4]):
                        a = str(word[0] + word[1])
                        return [a] + hyphenate(word[2:])
                    else:
                        if len(word) == 5:
                            word = "".join(word)
                            return [word]
                        elif isvowel(word[5]):
                            a = str(word[0] + word[1] + word[2] + word[3])
                            return [a] + hyphenate(word[4:])
                        else:
                            if len(word) == 6:
                                word = "".join(word)
                                return [word]
                            elif isvowel(word[6]):
                                a = str(word[0] + word[1] + word[2] + word[3] + word[4])
                                return [a] + hyphenate(word[5:])
                            else:
                                if len(word) == 7:
                                    word = "".join(word)
                                    return [word]
                                elif isvowel(word[7]):
                                    a = str(word[0] + word[1] + word[2] + word[3] + word[4] + word[5])
                                    return [a] + hyphenate(word[6:])
                                else:
                                    if len(word) == 8:
                                        word = "".join(word)
                                        return [word]
                                    elif isvowel(word[8]):
                                        a = str(word[0] + word[1] + word[2] + word[3] + word[4] + word[5] + word[6])
                                        return [a] + hyphenate(word[7:])
                                    else:
                                        word = "".join(word)
                                        return [word]
def isvowel(letter):
    if letter == "a" or letter == "e" or letter == "I" or letter == "i" or letter == "o" or letter == "O" or letter == "u" or letter == "U":
        return True
    else:
        return False
def execute():
    lst = []
    nm = raw_input()
    n = int(nm.split(" ")[0])
    m = int(nm.split(" ")[1])
    while True:
        newline = raw_input()
        if newline != "=":
            lst.append(newline)
            if newline[-1] == ".":
                del lst[-1]
                newline = newline.replace(".", "")
                lst.append(newline)
                lst.append(".")
            else:
                continue
        else:
            if lst[-1] != ".":
                del lst[-1]
                break
            else:
                break
    print lst
    def splitlines(lst):
        tra=[]
        while len(lst)!=0:
            if lst[0] != " ":
                tra=tra+ [lst[0].split(" ")]
            elif lst[0] == ".":
                tra=tra+["."]
            else:
                tra=tra+ [" "]
            lst=lst[1:]
        return tra
    def putspace(lst):
        lst1 = []
        for a in range(len(splitlines(lst))):
            if splitlines(lst)[a] != [" "] and splitlines(lst)[a] != ["."]:
                for x in splitlines(lst)[a]:
                    lst1 += [x] + [" "]
            elif splitlines(lst)[a] == ["."]:
                del lst1[-1]
                lst1 += ["."]
            else:
                lst1 += [" "]
        lst1.insert(0, " ")
        return lst1
    def hyphenlines(lst):
        newlst = []
        lst = putspace(lst)
        for x in range(len(lst)):
            if lst[x] == " ":
                newlst.append(lst[x])
            elif lst[x] == ".":
                newlst.append(lst[x])
            else:
                newlst = newlst + hyphenate(lst[x])
        return newlst
    def recordoccurence(lst):
        hyphenlist = hyphenlines(lst)
        hyphenlist1 = hyphenlines(lst)[1:]
        zippedlist = zip(hyphenlist, hyphenlist1)
        list_of_firstx = []
        list_of_firsts = []
        for x in range(len(zippedlist)):
            c = zippedlist[x][0]
            list_of_firsts.append(list_of_firstx)
            list_of_firstx = []
            for tpl in zippedlist:
                if c == tpl[0]:
                    list_of_firstx.append(tpl)
        last_one = [[(hyphenlines(lst)[-2],hyphenlines(lst)[-1])]]
        list_of_firsts = list_of_firsts + last_one
        return list_of_firsts[1:]
    def occurencefixer(lst):
        sortedlst = sorted(recordoccurence(lst))
        newsortedlst = []
        for k in range(len(sortedlst)):
            if sortedlst[k] != sortedlst[k - 1]:
                newsortedlst.append(sortedlst[k])
        return newsortedlst
    def starter_counter(lst):
        dict_of_exceptions = {}
        dict_of_exceptions["starter"] = {}
        for i in range(len(occurencefixer(lst))):
            dict1 = {}
            dict1[occurencefixer(lst)[i][0][0]] = dict(collections.Counter(occurencefixer(lst)[i]))
            value = dict1.values()[0]
            sorted_value = sorted(value.items(), key=operator.itemgetter(0))
            if occurencefixer(lst)[i][0][0] == " " or occurencefixer(lst)[i][0][0] == ".":
                for e in range(len(sorted_value)):
                    dict_of_exceptions["starter"][sorted_value[e][0][1]] = sorted_value[e][1]
        return dict_of_exceptions
    def counter(lst):
        dict_of_max = {}
        for i in range(len(occurencefixer(lst))):
            dict1 = {}
            dict1[occurencefixer(lst)[i][0][0]] = dict(collections.Counter(occurencefixer(lst)[i]))
            value = dict1.values()[0]
            sorted_value = sorted(value.items(), key=operator.itemgetter(0))
            sorted_value_fixer = []
            for p in range(len(sorted_value)):
                sorted_value_fixer += [sorted_value[p][1]]
                sorted_value_fixer = sorted(sorted_value_fixer, key=int,reverse=True)
            first_two = []
            for s in range(len(sorted_value)):
                if sorted_value_fixer[0] == sorted_value[s][1]:
                    first_two += [sorted_value[s]]
                    if len(first_two) < 2 and len(sorted_value) > 1:
                        if sorted_value_fixer[1] == sorted_value[s][1]:
                            if sorted_value_fixer[1] != sorted_value[s + 1][1]:
                                first_two += [sorted_value[s]]
                            else:
                                continue
            if len(first_two) < 2 and len(sorted_value) > 1:
                for u in range(len(sorted_value)):
                    if sorted_value_fixer[1] == sorted_value[u][1]:
                        first_two += [sorted_value[u]]
            dict_of_max[occurencefixer(lst)[i][0][0]] = {}
            if len(first_two) != 1:
                dict_of_max[occurencefixer(lst)[i][0][0]][first_two[0][0][1]] = first_two[0][1]
                dict_of_max[occurencefixer(lst)[i][0][0]][first_two[1][0][1]] = first_two[1][1]
            else:
                dict_of_max[occurencefixer(lst)[i][0][0]][first_two[0][0][1]] = first_two[0][1]
        return dict_of_max
    list_of_output = []
    firstoutput = random.choice(starter_counter(lst)["starter"].keys())
    list_of_output += [firstoutput]
    x = 0
    y = 0
    while True:
        if x >= n or y > m:
            break
        else:
            firstoutput = random.choice(counter(lst)[firstoutput].keys())
            list_of_output += [firstoutput]
            y += len(firstoutput)
            if firstoutput == " " or firstoutput == ".":
                x += 1
    list_of_output = "".join(list_of_output)
    print list_of_output

    
execute()

