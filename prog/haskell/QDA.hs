-- QDA.hs - Quantitative Data Analyzer of a line of at least 2 space-delimited doubles

import Data.List


range    xs =  last xs - head xs
midRange xs = (last xs + head xs) / 2


q2 xs =
    let len = length xs
        mid = div len 2
    in  if odd len then  xs !! mid
                   else (xs !! mid + xs !! (mid - 1)) / 2

q1 xs = q2 (take (length xs `div` 2) xs)
q3 xs = q2 (drop (length xs - length xs `div` 2) xs)

iqr      xs =  q3 xs - q1 xs
midHinge xs = (q3 xs + q1 xs) / 2


am xs = sum xs / fromIntegral (length xs)

gm xs = product xs ** recip (fromIntegral (length xs))

qm xs = sqrt (sum [x * x | x <- xs] / fromIntegral (length xs))

hm xs = recip (sum [recip x | x <- xs] / fromIntegral (length xs))


var xs = sum [(x - am xs) ** 2 | x <- xs] / fromIntegral (length xs)

sd xs = sqrt (var xs)

rsd xs = sd xs / abs (am xs)


skewness xs = sum [(x - am xs) ** 3 | x <- xs] / fromIntegral (length xs) / sd xs ** 3
kurtosis xs = sum [(x - am xs) ** 4 | x <- xs] / fromIntegral (length xs) / sd xs ** 4


main = do
    str <- getLine
    let ds = sort (map read (words str)) :: [Double]

    putStrLn ("                      Count | " ++ show (length ds))
    putStrLn ("                        Sum | " ++ show (sum ds))
    putStrLn ("                    Minimum | " ++ show (head ds))
    putStrLn ("                    Maximum | " ++ show (last ds))
    putStrLn ("                      Range | " ++ show (range ds))
    putStrLn ("                  Mid-Range | " ++ show (midRange ds))
    putStrLn ("             First Quartile | " ++ show (q1 ds))
    putStrLn ("            Second Quartile | " ++ show (q2 ds))
    putStrLn ("             Third Quartile | " ++ show (q3 ds))
    putStrLn ("        Interquartile Range | " ++ show (iqr ds))
    putStrLn ("                  Mid-Hinge | " ++ show (midHinge ds))
    putStrLn ("            Arithmetic Mean | " ++ show (am ds))
    putStrLn ("             Quadratic Mean | " ++ show (qm ds))
    putStrLn ("             Geometric Mean | " ++ show (gm ds))
    putStrLn ("              Harmonic Mean | " ++ show (hm ds))
    putStrLn ("                   Variance | " ++ show (var ds))
    putStrLn ("         Standard Deviation | " ++ show (sd ds))
    putStrLn ("Relative Standard Deviation | " ++ show (rsd ds))
    putStrLn ("                   Skewness | " ++ show (skewness ds))
    putStrLn ("                   Kurtosis | " ++ show (kurtosis ds))
