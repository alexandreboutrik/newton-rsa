import Data.Maybe (fromJust)
import Data.Fixed
import Data.Maybe

--- Power function with modulus
-- Compute 'num ^ pwr mod modulus'
pow :: Integer -> Integer -> Integer -> Maybe Integer
pow num pwr modulus | modulus == 0 = Nothing
                    | pwr < 0 = Just $ num ^ ((pwr + modulus) `mod` modulus) `mod` modulus
                    | otherwise = Just $ (num ^ pwr) `mod` modulus

--- Check if a number 'n' is prime using the trial division method
is_prime :: Integer -> Bool
is_prime n | n < 2 = False
           | otherwise = is_prime' n 2
           where
             is_prime' n divisor | divisor * divisor > n = True
                                 | n `mod` divisor == 0 = False
                                 | otherwise = is_prime' n (divisor + 1)

--- Extended Euclidean Algorithm (EEA)
-- Compute the modular inverse of 'a' under modulo 'n'
eea :: Integer -> Integer -> Maybe Integer
eea a n
    | a' == 1 = Just $ x `mod` n
    | otherwise = Nothing
      where
      (a', x, _) = egcd a n
      egcd :: Integer -> Integer -> (Integer, Integer, Integer)
      egcd 0 b = (b, 0, 1)
      egcd a b = (a', y' - (b `div` a) * x', x')
        where
        (a', x', y') = egcd (b `mod` a) a

--- Fermat-Euler Theorem
-- Compute the modular inverse of 'a' under modulo 'n'
fet :: Integer -> Integer -> Maybe Integer
fet a n
    | gcd a n /= 1 = Nothing
    | otherwise = pow a (-1) n

-- Find alpha
alpha :: Double -> Double -> Integer -> Integer -> Maybe Integer
alpha f_1 f_2 a n
    | (n == 0 || f_1 == 0 || f_2 == 0) = Nothing
    | otherwise = alpha' a n 1
    where
      alpha' a n x
        | x == a = Nothing
        | (a * ceiling (f_1 - x' * f_2)) `mod` n == 1 = Just $ x
        | otherwise = alpha' a n (x + 1)
        where
          x' = fromIntegral x

--- f1: Newton-Raphson (NR), one iteraction
f_1 :: Integer -> Integer -> Double -> Maybe Double
f_1 a n guess
    | (a == 0 || n == 0) = Nothing
    | otherwise = Just $ (guess - ((a' * guess) + 1) / a') `mod'` n'
    where
      a' = fromIntegral a
      n' = fromIntegral n

--- Correction Function
f_2 :: Integer -> Integer -> Double -> Maybe Double
f_2 a n guess
    | gcd a n /= 1 = Nothing
    | otherwise = f_2' a n guess (guess - 1)
    where
      f_2' a n guess old_guess
        | guess == old_guess = Just $ guess
        | otherwise = f_2' a n (guess * (2 - a' * guess / n')) guess
        where
          a' = fromIntegral a
          n' = fromIntegral n

my_print :: Show a => Maybe a -> IO()
my_print (Just x) = print x
my_print n = print n

main = do
  let e = 5
  let (p, q) = (17, 13)

  let n = (p - 1) * (q - 1)

  let d_1   = fromMaybe 0 (f_1 e n 1)
  let d_2   = fromMaybe 0 (f_2 e n 1)
  let a     = fromMaybe 0 (alpha d_1 d_2 e n)

  let d     = ceiling $ d_1 - fromIntegral a * d_2

  putStrLn $ "EEA: " ++ show (eea e n)
  putStrLn $ "FET: " ++ show (fet e n)
  putStrLn $ "NR:  Just " ++ show d
  putStrLn $ "alpha: " ++ show a ++ "   f_1: " ++ show d_1 ++ "   f_2: " ++ show d_2
