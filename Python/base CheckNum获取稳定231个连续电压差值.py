# base https://github.com/benchover/checkNum

import xlrd
import random


list1 = [] #建立一个列表存放电压值
nrows_list=[] #建立空的横列表
ncols_list=[] #建立空的竖列表
n_start = 0   # 匹配成功的起始位置
flag = 0    # 是否找到231 的开头

def read_excle():
	file = xlrd.open_workbook("qqq.xlsx")
	sheets=filename.nsheets
	table = file.sheets()[0]
	print(file)

#getsheet
def read_sheet():
	sheet_list = file.sheet_by_names('2OA')
	print(sheet_list)

#print 'sheet_name:' file.sheet_names()
#print "row num:", file.nrows  # get sheet all rows number
#print "col num:", file.ncols  # get sheet all columns number
#获取行列数
def read_values():
	nrows = sheet_list.nrows
	ncols = sheet_list.ncols
	print("values：{}行×{}列".format(nrows,ncols))
	
def coli():
	print(table.row_values(0))
	for coli in range():
        print(nrows_values(coli)) #打印D列表
	coli = list1()
	list2 = list1[:]

def range():
	for i, num in enumerate(list2):
		if flag == 0:  # 找头
			if num < 50:
				# 找到头了
				flag = 1
				n_start = i
		elif flag == 1:  # 已有头
			if i - n_start == 231:
				# 数量够了
				break
			if num >= 50:
				if i - n_start < 231:
					# 说明不足231个就完了
					# 重新找头
					flag = 0
					n_start = 0
					continue

# 结果数组
out_list = []

for i in range(231):
    out_list.append(list2[n_start + i])
print(out_list)

if __name__ == '__main__':
    read_excle()
    read_sheet()
    read_values()
    coli()
    range()
