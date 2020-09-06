Hello, here is my work environment space

i'm a college student and a low-level developer.
i love use code to Automate work environment.
the beginning  of creating I forgot to set the repository up as private.
;p



------

git的一些奇技淫巧

##git reset 

假设有一些 commits

A - B - C (master)
HEAD 指向 C， 并且暂存区（stage，或称为 index）matches C.

git reset --soft/mixed/hard解释

###### soft 保持暂存区可以提交修改。

当使用 git reset --soft B 时，master 和 HEAD 指向 B，但是依然保留了 C 添加跟踪的文件，此时会将这些文件放入暂存区中，显示为已缓存。同时工作区中修改的文件，显示为未缓存。

###### mixed 保持工作区不变，重置索引。

当使用 git reset --mixed B 时，master 和 HEAD 指向 B，这时候 C 添加跟踪的文件仍然会在，但是会显示为未缓存（不是版本控制），而当前工作目录中的修改内容，仍然会在，显示未缓存的状态

（如果不知道怎么选，默认使用 mixed）

###### hard 重置索引和工作区（丢弃所有本地变更）

当使用 git reset --hard B 时，C 添加跟踪的文件，以及当前工作目录中的修改内容，都会丢失。
