<h1 align="center">bad repository</h1>

<h4 align="center">Hello, here is my work environment space
<h4 align="center">i'm a college student and a low-level developer.
<h4 align="center">i love use code to Automate work environment.
<h4 align="center">sometimes i change my work exprcise on home and school.
<h4 align="center">the beginning of creating I forgot to set the repository up as private ;p

------

### git-tips

##### git reset --soft/mixed/hard解释

if i have some commits need to squash D into C commit

```
A - B - C - D (master)
	↑
	HEAD
		
{ work direatory (unstage)      `git add ..`
{ stage          (staged)       `git commit -s..`
```

##### soft 保持暂存区  (keep stage) 是提交C，D的文件仍然被跟踪，可以提交修改。

HEAD point to C, the stage/index matches C, and D's changes on work diretory.

当使用 git reset --soft B 时，master 和 HEAD 指向 B，但是依然保留了 C 添加跟踪的文件，此时会将这些文件放入暂存区中，显示为已缓存。同时工作区中修改的文件，显示为未缓存。


##### mixed 保持工作区（keep work direatory）不变，重置索引。

当使用 git reset --mixed B 时，master 和 HEAD 指向 B，这时候 C 添加跟踪的文件仍然会在，但是会显示为未缓存（不是版本控制），而当前工作目录中的修改内容，仍然会在，显示未缓存的状态

（如果不知道怎么选，默认使用 mixed）


##### hard 重置索引和工作区（Discard all changes）

当使用 git reset --hard B 时，C 添加跟踪的文件，以及当前工作目录中的修改内容，都会丢失。

