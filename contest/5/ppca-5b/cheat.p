(function (FunctionAAAAAAAB VariableAAAAAAABArray)
  (array.set VariableAAAAAAABArray 0 (scan)))

(function (FunctionAAAAAAAD VariableAAAAAAAFArray)
  (array.set VariableAAAAAAAFArray 0 0))

(function (FunctionAAAAAAAE VariableAAAAAAAF VariableAAAAAAAFArray VariableAAAAAAAH)
  (array.set VariableAAAAAAAFArray 0 (Function+ VariableAAAAAAAF (Function* VariableAAAAAAAH VariableAAAAAAAH))))

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
    (set VariableAAAAAAAC (array.scan VariableAAAAAAAB))
    (print (FunctionAAAAAAAC VariableAAAAAAAC VariableAAAAAAAB))))

(function (FunctionAAAAAAAC VariableAAAAAAAD VariableAAAAAAAE)
  (block
    (if (Function== VariableAAAAAAAE 0)
      (return 0))
    (if (Function!= VariableAAAAAAAE 0)
      (block
        (set VariableAAAAAAAFArray (array.create 1))
        (FunctionAAAAAAAD VariableAAAAAAAFArray)
        (set VariableAAAAAAAF (array.get VariableAAAAAAAFArray 0))))
    (for
      (set VariableAAAAAAAG 0)
      (Function< VariableAAAAAAAG VariableAAAAAAAE)
      (set VariableAAAAAAAG (Function+ VariableAAAAAAAG 1))
      (block
        (set VariableAAAAAAAH (array.get VariableAAAAAAAD VariableAAAAAAAG))
        (set VariableAAAAAAAFArray (array.create 1))
        (FunctionAAAAAAAE VariableAAAAAAAF VariableAAAAAAAFArray VariableAAAAAAAH)
        (set VariableAAAAAAAF (array.get VariableAAAAAAAFArray 0))))
    (return VariableAAAAAAAF)))

