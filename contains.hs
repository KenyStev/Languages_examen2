len [] = 0
len [_] = 1
len (_:ss) = 1 + (len ss)

slice [] _ = []
slice (a:ss) x = if x > 0
                    then a:(slice ss (x-1))
                    else []

contains [] [] = True
contains (ass) [] = False
contains (ass) (x:xs) = if (slice (x:xs) (len ass)) == ass
                        then True
                        else contains ass xs