import Data.Maybe (fromJust)

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
et :: Integer -> Integer -> Maybe Integer
et a n | gcd a n /= 1 = Nothing
       | otherwise = pow a (-1) n

--- Newton-Raphson method (NR)
-- Compute the modular inverse of 'a' under modulo 'n'
--- WARNING: not working
--newton :: Integer -> Integer -> Integer -> Integer -> Maybe Integer
--newton a n guess iter | gcd a n /= 1 = Nothing 
--                      | iter == 0 = Just $ guess `mod` n
--                      | otherwise = newton a n new_guess (iter - 1)
--                      where
--                        new_guess = (guess * (2 - ((a * guess) `div` n)))

main = do
  print $ eea 7 120
  print $ et 7 120
  -- print $ newton 7 120 1 50
