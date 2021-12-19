

# Digital-Image-Processing(数字图像处理)

### shiyan6 pattern

------

### ·一、实验目的

​			提高动手能力



------

### ·二、实验环境

​	(1)Python 3.9.7

​	(2)Anaconda 2021-5

​	(3)Vscode 1.62.3

​	(4)Windows10



------

### ·三、实验原理



**直方图均衡**

​		直方图是对图像的一种抽象表示方式。借助修改或变换图像直方图，可以改变图像像素的灰度分布。可以达到图像增强的效果。

​		直方图均衡化主要用于增强动态范围偏小的图像的反差。其基本思想是把原始图像的直方图变换为整个灰度范围内均匀分布，这样就增加了像素灰度值的动态范围，从而达到增强图像对比度的效果。

​		灰度直方图的函数式，写成归一化的概率表达式，f是一个单值单增的函数，可以保证灰度级变换之后，仍然保持灰度级的排列次序。n是图像中像素的总数。

 

​         																				       ![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image002.png)

  

**傅里叶变换**

​		计算机中储存的数字图像是离散的类型，因此利用离散傅里叶变换就可以对图像信号方面进行处理。对于数字图像这种离散的信号，频率大小表示信号变化的剧烈成都或者说是信号变化的快慢。

  一个图像为M*N的图像f(x,y)进过离散傅里叶变换得到F(u,v)，那么一般的公式为：

![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image004.png)

 

它的反变换就是

![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image006.png)



**维纳滤波**

  维纳滤波是比较早期的改进的逆滤波算法，它是使得原始图像与复原图像之

间的均方误差最小的复原方法，设计简单,维纳滤波算法计算量低，抗噪性能高，

已被广泛应用于图像处理领域并改进成各种高级算法,至今任然是比较实用的算

法，特别对复原噪声的抑制也有很好的效果，下面是其计算式:

  																		        ![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image008.png)

其中F(u, V),H(u,v),G(u,v)分别是清晰复原图的频谱，模糊核的频谱以及模糊图的频谱，K为噪声抑制因子，K是与原始图和噪声功率谱之比有关的因子。依据逆滤波基本原则，加入抑制噪声因子，适当调节K值(在0.001和0.01之间的效果较好)可在在高噪下可取的良好复原效果。



**编码冗余：**

对于图像来说，可以假设一个离散随机变量表示图像的灰度级，并且每个灰度级（rk）出现的概率为pr

   																	          ![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image010.png)

这里L是灰度级数，nk是第k个灰度级在图像中出现的次数， n是图像中的像素总数。



**平均比特数：**

对应一张图像上每个像素所采用的平均比特数，L(r_k)为灰度级r_k所使用的比特数，p(r_k)表示对应灰度级的概率；

​     												       ![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image012.png)

将表示每个灰度级值所用的比特数和灰度级出现的概率相乘，将所得乘积相加后得到不同灰度级值的平均码字长度。

 

**熵**：

它定义了观察单个信源输出得到的平均信息量。如果某种编码的平均比特数越接近熵，則编码冗余越小。

   																	          ![img](file:///C:/Users/Gah0/AppData/Local/Temp/msohtmlclip1/01/clip_image014.png)



**椒盐噪声：**

椒盐噪声是数字图像中的常见噪声，一般是图像传感器、传输信道及解码处理等产生的黑白相间的亮暗点噪声，椒盐噪声常由图像切割产生。椒盐噪声是指两种噪声：盐噪声和椒噪声。盐噪声一般是白色噪声，椒噪声一般为黑色噪声。前者属于高灰度噪声，或者属于低灰度噪声，一般两种噪声同时出现，呈现黑白杂点。去除椒盐噪声常用的方法是中值滤波。

 

**区域增长：**

区域生长是一种串行区域分割的图像分割方法。**区域生长是指从某个像素出发，按照一定的准则，逐步加入邻近像素，当满足一定的条件时，区域生长终止**。

 

------

### ·四、实验步骤

对给定的一幅简单背景动植物图做以下操作：

 1）对图像进行增强和直方图均衡化处理 

 2）编程实现对图像二维离散傅里叶变换和二维离散傅里叶逆变换；

 3）对频域图像进行维纳滤波处理；

 4）先对图像添加“椒盐”噪声，然后再对其进行复原；

 5）压缩图像的编码冗余、像素间冗余并求出其压缩率；

 6）对图像进行边缘检测；

 7）采用区域增长和分裂合并算法分割图像；

 8）求出叶子的周长、面积；（选作）



------

### ·五、实验代码

[本目录下shiyan6.py](https://github.com/Gah0/Scripts/blob/master/Python/DIP/shiyan6.py)

**程序函数定义**

(1)图像增强之直方图均衡

```python
cv2.equalizeHist(img)
```

(2)低通滤波（傅里叶变换与逆变换）处理

```python
def ft(image):
```

(3)对频域图像进行维纳滤波处理

```python
Def vinr(image):
```

(4)对图像添加椒盐噪声

```python
Def SaltAndPepper(src,percetage):
```

(5)计算编码冗余，平均码长

```python
Def total_entropy(image):
```

(6)转换为二进制

```python
Def dec2bin(p)
```

(7)对图像边缘检测

```python
Def find(image):
```

(8)区域增长分割图像

储存当前点坐标的类

```python
Class Point(object):
```

领域算子

```python
Def selectcon(p):
```

区域增长

```python
Def region(img,seeds,thresh,p=1):
```

(9)求叶子的边长（周长），面积

```python
Def calcarea(contours):
```



### ·六、实验结果

<img src="https://raw.githubusercontent.com/Gah0/Scripts/master/Python/DIP/cao.png" alt="cao.png" style="zoom:25%;" />

![figure1](https://raw.githubusercontent.com/Gah0/Scripts/master/Python/DIP/figure1.png)

![figure2](https://raw.githubusercontent.com/Gah0/Scripts/master/Python/DIP/figure2.png)

![figure3](https://raw.githubusercontent.com/Gah0/Scripts/master/Python/DIP/figure3.jpg)

