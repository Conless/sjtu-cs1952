Visiting: (set n (scan))
(set VariableAAAAAAAB 7254741)
(FunctionAAAAAAAB VariableAAAAAAAB)
Visiting: (set xs (array.scan n))
Visiting: (print (sum^2 xs n))
Visiting: (set VariableAAAAAAAB (scan))
(set VariableAAAAAAAF 431030797)
(FunctionAAAAAAAC VariableAAAAAAAF)
Visiting: (set VariableAAAAAAAD (array.scan n))
Visiting: (print (sum^2 xs n))
Visiting: (if (== length 0)
  (return 0))
Visiting: (if (!= length 0)
  (set sum 0))
Visiting: (for
  (set i 0)
  (< i length)
  (set i (+ i 1))
  (block
    (set value (array.get array i))
    (set sum (+ sum (* value value)))))
Visiting: (set value (array.get array i))
Visiting: (set sum (+ sum (* value value)))
(set VariableAAAAAAAN 448329730)
(FunctionAAAAAAAH VariableAAAAAAAN VariableAAAAAAAP)
Visiting: (return sum)
Visiting: (if (== length 0)
  (return 0))
Visiting: (if (!= length 0)
  (set VariableAAAAAAAN 0))
Visiting: (for
  (set VariableAAAAAAAO 0)
  (< i length)
  (set VariableAAAAAAAO (+ i 1))
  (block
    (set VariableAAAAAAAQ (array.get array i))
    (set VariableAAAAAAAN (+ sum (* value value)))))
Visiting: (set VariableAAAAAAAQ (array.get array i))
Visiting: (set VariableAAAAAAAN (+ sum (* value value)))
(set VariableAAAAAAAS 1575170495)
(FunctionAAAAAAAL VariableAAAAAAAS VariableAAAAAAAY VariableAAAAAAAZ)
Visiting: (return sum)










(function (Function+ VariableA VariableB)
  (block
    (set VariableC (+ VariableA VariableB))
    (return VariableC)))

(function (Function- VariableA VariableB)
  (block
    (set VariableC (- VariableA VariableB))
    (return VariableC)))

(function (Function* VariableA VariableB)
  (block
    (set VariableC (* VariableA VariableB))
    (return VariableC)))

(function (Function/ VariableA VariableB)
  (block
    (set VariableC (/ VariableA VariableB))
    (return VariableC)))

(function (Function% VariableA VariableB)
  (block
    (set VariableC (% VariableA VariableB))
    (return VariableC)))

(function (Function< VariableA VariableB)
  (block
    (set VariableC (< VariableA VariableB))
    (return VariableC)))

(function (Function> VariableA VariableB)
  (block
    (set VariableC (> VariableA VariableB))
    (return VariableC)))

(function (Function<= VariableA VariableB)
  (block
    (set VariableC (<= VariableA VariableB))
    (return VariableC)))

(function (Function>= VariableA VariableB)
  (block
    (set VariableC (>= VariableA VariableB))
    (return VariableC)))

(function (Function== VariableA VariableB)
  (block
    (set VariableC (== VariableA VariableB))
    (return VariableC)))

(function (Function!= VariableA VariableB)
  (block
    (set VariableC (!= VariableA VariableB))
    (return VariableC)))

(function (Function|| VariableA VariableB)
  (block
    (set VariableC (|| VariableA VariableB))
    (return VariableC)))

(function (Function&& VariableA VariableB)
  (block
    (set VariableC (&& VariableA VariableB))
    (return VariableC)))

(function (main)
  (block
    (set VariableAAAAAAAF 431030797)
    (FunctionAAAAAAAC VariableAAAAAAAF)
    (set VariableAAAAAAAJ (array.scan VariableAAAAAAAI))
    (print (FunctionAAAAAAAD VariableAAAAAAAK VariableAAAAAAAI))))

(function (FunctionAAAAAAAD VariableAAAAAAAL VariableAAAAAAAM)
  (block
    (if (Function== VariableAAAAAAAM 0)
      (return 0))
    (if (Function!= VariableAAAAAAAM 0)
      (block
        (set VariableAAAAAAAS 886258059)
        (FunctionAAAAAAAI VariableAAAAAAAS)))
    (for
      (block
        (set VariableAAAAAAAT 1720017808)
        (FunctionAAAAAAAJ VariableAAAAAAAT))
      (Function< VariableAAAAAAAU VariableAAAAAAAM)
      (block
        (set VariableAAAAAAAT 1595906500)
        (FunctionAAAAAAAK VariableAAAAAAAT VariableAAAAAAAU))
      (block
        (set VariableAAAAAAAX (array.get VariableAAAAAAAL VariableAAAAAAAU))
        (set VariableAAAAAAAS 1575170495)
        (FunctionAAAAAAAL VariableAAAAAAAS VariableAAAAAAAY VariableAAAAAAAZ)))
    (return VariableAAAAAABA)))

(function (FunctionAAAAAAAB VariableAAAAAAAB)
  (set VariableAAAAAAAF (scan)))

(function (FunctionAAAAAAAC VariableAAAAAAAF)
  (set VariableAAAAAAAF (scan)))

(function (FunctionAAAAAAAE VariableAAAAAAAN)
  (set VariableAAAAAAAS 0))

(function (FunctionAAAAAAAF VariableAAAAAAAO)
  (set VariableAAAAAAAT 0))

(function (FunctionAAAAAAAG VariableAAAAAAAO)
  (set VariableAAAAAAAT (+ i 1)))

(function (FunctionAAAAAAAH VariableAAAAAAAN VariableAAAAAAAP)
  (set VariableAAAAAAAS (+ sum (* value value))))

(function (FunctionAAAAAAAI VariableAAAAAAAS)
  (set VariableAAAAAAAS 0))

(function (FunctionAAAAAAAJ VariableAAAAAAAT)
  (set VariableAAAAAAAT 0))

(function (FunctionAAAAAAAK VariableAAAAAAAT VariableAAAAAAAU)
  (set VariableAAAAAAAT (+ i 1)))

(function (FunctionAAAAAAAL VariableAAAAAAAS VariableAAAAAAAY VariableAAAAAAAZ)
  (set VariableAAAAAAAS (+ sum (* value value))))

