type Buffer* = object
  len: uint
  `ptr`: ptr uint8

type Result* = object
  singleBuff: Buffer
  lenBuffArr: uint
  ptrBuffArr: ptr Buffer

proc my_func(r: ptr Result) {.importc: "my_func".}

proc free_result(r: ptr Result) {.importc: "free_result".}

var myResult {.noinit.}: Result = Result()

var myResultPtr = addr myResult

my_func(myResultPtr)


proc toSeq(b: Buffer): seq[byte] =
    var uncheckedArr = cast[ptr UncheckedArray[byte]](b.`ptr`)
    var mySequence = newSeq[byte](b.len)
    for i in 0..b.len-1:
        mySequence[i] = uncheckedArr[i]
    return mySequence

proc toBufferSeq(buffLen: uint, buffPtr: ptr Buffer): seq[Buffer] =
    var uncheckedArr = cast[ptr UncheckedArray[Buffer]](buffPtr)
    var mySequence = newSeq[Buffer](buffLen)
    for i in 0..buffLen-1:
        mySequence[i] = uncheckedArr[i]
    return mySequence

if myResultPtr == nil:
    echo "ERROR!"
else:
    echo myResultPtr[]
    
    echo "Single buffer value:"
    echo toSeq(myResult.singleBuff)

    echo "Buffer array values:"
    let bufSeq = toBufferSeq(myResult.lenBuffArr, myResult.ptrBuffArr)
    for i in 0..bufSeq.len - 1:
        echo "Buffer ", i, ": ", toSeq(bufSeq[i])

    free_result(myResultPtr)
