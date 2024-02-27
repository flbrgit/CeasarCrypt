# CeasarCrypt
Fast High-End Encryption Algorithm

## Algorithm Overview

This encryption algorithm combines the principles of the Caesar Cipher with the XOROSHIRO128 pseudo-random number generator to enhance security and eliminate predictability. The algorithm introduces a novel approach by randomly shuffling the alphabet using the Fisher-Yates Shuffle. Additionally, the index of each character plays a role in the encryption process to avoid one-to-one mappings of identical characters.

## Key Components

XOROSHIRO128 PRNG: A robust pseudo-random number generator is employed for key generation. The XOROSHIRO128 algorithm ensures unpredictability and meets rigorous testing standards.
Fisher-Yates Shuffle: To eliminate patterns in the ciphertext, the algorithm shuffles the alphabet in a genuinely random manner.
Index-Based Shift: Each character's shift is influenced not only by the fixed key value but also by its position in the alphabet. This prevents repeated characters from encrypting to the same character in the ciphertext.

## Security Measures

Elimination of Patterns: The Fisher-Yates Shuffle guarantees that the resulting ciphertext lacks any recognizable patterns, making frequency analysis impractical.
XOROSHIRO128 Strength: Leveraging a strong PRNG ensures a high degree of unpredictability, essential for a secure encryption scheme.

## Safety Considerations

Key Length: The security of the algorithm is contingent on the length of the XOROSHIRO128 seed. A longer seed enhances security but requires careful handling to avoid compromises.
## Conclusion
The XOROSHIRO128-based Caesar Cipher introduces a unique fusion of classic and modern cryptographic principles, aiming to provide a secure and unpredictable encryption method suitable for various applications.

## Note
This algorithm is presented for educational purposes, and its security should be thoroughly evaluated before deployment in sensitive contexts.

## Copyright

Copyright © Florian Briksa 2024. All rights reserved.
