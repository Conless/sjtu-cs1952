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
    (set VariableAAAAAAABArray (array.create 1))
    (FunctionAAAAAAAB VariableAAAAAAABArray)
    (set VariableAAAAAAAB (array.get VariableAAAAAAABArray 0))
    (set VariableAAAAAAAE (array.scan VariableAAAAAAAB))
    (print (FunctionAAAAAAAC VariableAAAAAAAC VariableAAAAAAAB))))

(function (FunctionAAAAAAAC VariableAAAAAAAF VariableAAAAAAAG)
  (block
    (if (Function== VariableAAAAAAAG 0)
      (return 0))
    (if (Function!= VariableAAAAAAAG 0)
      (block
        (set VariableAAAAAAAHArray (array.create 1))
        (FunctionAAAAAAAD VariableAAAAAAAHArray)
        (set VariableAAAAAAAH (array.get VariableAAAAAAAHArray 0))))
    (for
      (block
        (set VariableAAAAAAAIArray (array.create 1))
        (FunctionAAAAAAAE VariableAAAAAAAIArray)
        (set VariableAAAAAAAI (array.get VariableAAAAAAAIArray 0)))
      (Function< VariableAAAAAAAI VariableAAAAAAAG)
      (block
        (set VariableAAAAAAAIArray (array.create 1))
        (FunctionAAAAAAAF VariableAAAAAAAI VariableAAAAAAAIArray)
        (set VariableAAAAAAAI (array.get VariableAAAAAAAIArray 0)))
      (block
        (set VariableAAAAAAAL (array.get VariableAAAAAAAF VariableAAAAAAAI))
        (set VariableAAAAAAAHArray (array.create 1))
        (FunctionAAAAAAAG VariableAAAAAAAH VariableAAAAAAAHArray VariableAAAAAAAJ)
        (set VariableAAAAAAAH (array.get VariableAAAAAAAHArray 0))))
    (return VariableAAAAAAAH)))

(function (FunctionAAAAAAAB VariableAAAAAAABArray)
  (array.set VariableAAAAAAABArray 0 (scan)))

(function (FunctionAAAAAAAD VariableAAAAAAAHArray)
  (array.set VariableAAAAAAAHArray 0 0))

(function (FunctionAAAAAAAE VariableAAAAAAAIArray)
  (array.set VariableAAAAAAAIArray 0 0))

(function (FunctionAAAAAAAF VariableAAAAAAAI VariableAAAAAAAIArray)
  (array.set VariableAAAAAAAIArray 0 (+ i 1)))

(function (FunctionAAAAAAAG VariableAAAAAAAH VariableAAAAAAAHArray VariableAAAAAAAJ)
  (array.set VariableAAAAAAAHArray 0 (+ sum (* value value))))

