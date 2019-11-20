# lesson 4
# list被定义成一个列表，包含了不同类型的对象，使用type()函数返回变量类型
# 列表：有序的/可变/对象集合 list
list1 = [1,"a",True,[1,2,3],("a","b","c")]
print(list1)
type(list1)

extra=[caixukun，xiaoyang]
list1.append(extra)
print(list1)

list1.remove
list1.pop("1")
list1.insert("3","caixukun")
list2=[4,5]
list1.extend(list2)

#list3是个假的列表
list3 = list1
# 这个才是真的克隆列表
list5 = list1.copy()
list4 = list1[::-1] # 步长为-1

# 被定义成一个元组，同样包含了不同的对象类型
# 元组:有序的/不可变/对象集合 tuple
tuple = (1,"a",Ture,[1,2,3],("d","e","f"))
print(tuple)
type(tuple)

# ========================

#dict被定义为一个字典，包含多个键/值(key/value)对，每一组键/值对用逗号分隔
#字典：无序的键/值对集合dict
dict = {'gender':'female',
        'hobby':'sing, dance,rap and basketball',
        'music':'鸡你太美'}
print(dict)
type(dict)

# groups是一个集合，无序不重复的唯一对象集合set
# 集合：无序的唯一对象集合set
groups = {'s','h','e','e','e','p'}
print(groups)
type(groups)

#isinstance() 函数：判断一个对象是否是一个已知的类型。
e = {}
isinstance(e,set)#判断是否为空集合
