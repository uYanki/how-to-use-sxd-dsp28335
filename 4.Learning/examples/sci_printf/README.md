gmake -k -j 12 all -O

# SCI

## 28335_RAM_lnk.cmd

* 增大堆栈

使用 SCIx_Printf 是会分配大段堆空间，若输出有乱码，可能是堆过小导致。

![image-20230725225243487](.assest/README/image-20230725225243487-1690566110833.png)

* 启用浮点支持

![image-20230726233959203](.assest/README/image-20230726233959203.png)

* 内存分配

stdio.h 这个库占的体积蛮大的，需增大 RAM，编译才能通过。

注：改了某行长度（length），就得改下行的起始地址（origin）

![image-20230725225646042](.assest/README/image-20230725225646042-1690566110835.png)

程序段也需进行更改：

![image-20230725225858977](.assest/README/image-20230725225858977-1690566110835.png)

## F28335.cmd

注：若使用了 %f 等浮点格式化，导致 进入 `ILLEGAL_ISR` 中断，程序无法继续允许。

![image-20230726233823178](.assest/README/image-20230726233823178.png)

可关闭浮点支持，即修改为 `nofloat`。

![image-20230726233909687](.assest/README/image-20230726233909687.png)

怎么发现的？调试模式。

![image-20230726234431582](.assest/README/image-20230726234431582.png)

#### CIO...

# Demo

配置 CMD

![image-20230729014312238](.assest/README/image-20230729014312238.png)

切换编译用的 CMD：

![image-20230729014347433](.assest/README/image-20230729014347433.png)

切换代码段（需配合对应的 CMD）：

![image-20230729015227759](.assest/README/image-20230729015227759.png)

