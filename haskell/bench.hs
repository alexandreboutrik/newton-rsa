import Methodos
import Rsa (is_prime, gen_e)

import Data.Maybe (fromJust)
import Data.Maybe -- fromMaybe
import Data.Array (Array, listArray, (!), elems)

import System.Exit (exitSuccess, exitFailure)

import Criterion.Main (defaultMain, bench, nf)

-- Generate primes
gen_p :: Integer -> Int -> [Integer]
gen_p start count = take count $ filter is_prime [ start .. ]

-- Make our input array
array_primes :: Array Int Integer
array_primes = listArray (0, 9) (gen_p 1000000000000 10)

-- Benchmark
main :: IO ()
main = do

  defaultMain
    [ bench ("FET (p=" ++ show (array_primes ! i) ++ ",q=" ++ show (array_primes ! (i + 1)) ++ ")") $ nf (uncurry fet) (e, phi)
    | i <- [ 0, 2 .. 198 ]
    , let p = array_primes ! i
          q = array_primes ! (i + 1)
          phi = (p - 1) * (q - 1)
          e = fromMaybe 0 (gen_e phi)
    ]
