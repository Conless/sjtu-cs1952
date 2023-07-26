; 注释以分号开头
; 程序入口点为 main 函数
(function (main)
  ; 多条语句需要用代码块包裹起来
  (block
    ; 读入一个整数 n
    ; scan 是一个内置函数
    (set n (scan))
    ; 读入 n 个整数, 存入一个数组
    ; array.scan 也是一个内置函数
    (set xs (array.scan n))
    ; 输出答案
    (print (sum^2 xs n))))

; sum^2 是一个合法的变量名/函数名
(function (sum^2 array length)
  (block
    ; if 语句
    ; == 和 != 是内置函数 (下面的 < + * 都是内置函数)
    (if (== length 0)
      (return 0))
    (if (!= length 0)
      ; 变量的作用域为整个函数;
      ; 即使退出了 if 语句, 在后面 for 中也能使用 sum 变量
      (set sum 0))
    ; for 语句
    (for
      (set i 0) ; i = 0
      (< i length) ; i < length
      (set i (+ i 1)) ; ++i
      (block
        ; value = array[i]
        (set value (array.get array i))
        ; sum = sum + value * value
        (set sum (+ sum (* value value)))))
    ; 返回平方和
    (return sum)))