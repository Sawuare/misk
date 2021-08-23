-- qda.hs - a quantitative data analyzer

import Data.List

median xs count
  | odd count =  xs !! mid
  | otherwise = (xs !! mid + xs !! (mid - 1)) / 2
  where mid = div count 2

main = do
  line <- getLine

  let ds = sort (map read (words line)) :: [Double]

  let count = length ds
  let total = sum ds

  let min = head ds
  let max = last ds

  let range    =  max - min
  let midRange = (max + min) / 2

  let half = div count 2

  let q2 = median ds count

  let q1 = if count == 1 then q2 else median (take half ds) half
  let q3 = if count == 1 then q2 else median (drop (count - half) ds) half

  let iqr      =  q3 - q1
  let midHinge = (q3 + q1) / 2

  let am = total / fromIntegral count
  let gm = product ds ** recip (fromIntegral count)
  let qm = sqrt (sum [d * d | d <- ds] / fromIntegral count)
  let hm = recip (sum [recip d | d <- ds] / fromIntegral count)

  let var = sum [(d - am) ** 2 | d <- ds] / fromIntegral count
  let sd  = sqrt var
  let rsd = sd / abs am

  let skewness = sum [(d - am) ** 3 | d <- ds] / fromIntegral count / sd ** 3
  let kurtosis = sum [(d - am) ** 4 | d <- ds] / fromIntegral count / sd ** 4

  putStrLn ("                      Count = " ++ show count)
  putStrLn ("                      Total = " ++ show total)
  putStrLn ("                    Minimum = " ++ show min)
  putStrLn ("                    Maximum = " ++ show max)
  putStrLn ("                      Range = " ++ show range)
  putStrLn ("                  Mid-Range = " ++ show midRange)
  putStrLn ("             First Quartile = " ++ show q1)
  putStrLn ("            Second Quartile = " ++ show q2)
  putStrLn ("             Third Quartile = " ++ show q3)
  putStrLn ("        Interquartile Range = " ++ show iqr)
  putStrLn ("                  Mid-Hinge = " ++ show midHinge)
  putStrLn ("            Arithmetic Mean = " ++ show am)
  putStrLn ("             Quadratic Mean = " ++ show qm)
  putStrLn ("             Geometric Mean = " ++ show gm)
  putStrLn ("              Harmonic Mean = " ++ show hm)
  putStrLn ("                   Variance = " ++ show var)
  putStrLn ("         Standard Deviation = " ++ show sd)
  putStrLn ("Relative Standard Deviation = " ++ show rsd)
  putStrLn ("                   Skewness = " ++ show skewness)
  putStrLn ("                   Kurtosis = " ++ show kurtosis)
