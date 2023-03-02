/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the PSoC 6 MCU and OPTIGA Trust M
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
* The MIT License
*
* Copyright (c) 2021 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include "optiga_example.h"
#include "optiga/common/optiga_lib_logger.h"
#include "optiga/pal/pal.h"

/*******************************************************************************
* Macros
*******************************************************************************/

#define EXAMPLE_MODULE "[optiga example]  : "

#define MESSAGE(msg) \
        optiga_lib_print_message(msg, EXAMPLE_MODULE, \
        OPTIGA_LIB_LOGGER_COLOR_LIGHT_GREEN);
                            
#define ERROR(msg) \
        optiga_lib_print_message(msg, OPTIGA_SHELL_MODULE, \
        OPTIGA_LIB_LOGGER_COLOR_YELLOW);

#define TAB "                    "

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

extern void example_optiga_init(void);
extern void example_optiga_deinit(void);
extern void example_optiga_crypt_hash (void);
extern void example_optiga_crypt_ecc_generate_keypair(void);
extern void example_optiga_crypt_ecdsa_sign(void);
extern void example_optiga_crypt_ecdsa_verify(void);
extern void example_optiga_crypt_ecdh(void);
extern void example_optiga_crypt_random(void);
extern void example_optiga_crypt_tls_prf_sha256(void);
extern void example_optiga_crypt_rsa_generate_keypair(void);
extern void example_optiga_crypt_rsa_sign(void);
extern void example_optiga_crypt_rsa_verify(void);
extern void example_optiga_crypt_rsa_decrypt_and_export(void);
extern void example_optiga_crypt_rsa_decrypt_and_store(void);
extern void example_optiga_crypt_rsa_encrypt_message(void);
extern void example_optiga_crypt_rsa_encrypt_session(void);
extern void example_optiga_crypt_hash_data(void);
extern void example_optiga_crypt_symmetric_encrypt_decrypt_ecb(void);
extern void example_optiga_crypt_symmetric_encrypt_decrypt_cbc(void);
extern void example_optiga_crypt_symmetric_encrypt_cbcmac(void);
extern void example_optiga_crypt_hmac(void);
extern void example_optiga_crypt_hkdf(void);
extern void example_optiga_crypt_symmetric_generate_key(void);
extern void example_optiga_hmac_verify_with_authorization_reference(void);
extern void example_optiga_crypt_clear_auto_state(void);

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CM4 CPU. It initialises all optiga relevant 
* routines nad executes dedicated cryptography relevant examples.
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    
    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();


    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** OPTIGA: Cryptography Example ****************** \r\n\n");

    /*
      Initialise the chip with this function
    */
    example_optiga_init();

    /* 
      Examples are standalone and called one-by-one
    */
    MESSAGE("Initializing OPTIGA for example demonstration...");

    MESSAGE("1. Hash Example");
    MESSAGE("1 Step: Hash given data with Start, Update and Finalize calls");
    example_optiga_crypt_hash();

    MESSAGE("2. Generate an ECC Key pair Example");
    MESSAGE("1 Step: Generate ECC NIST P-256 Key Pair and export the public key");
    example_optiga_crypt_ecc_generate_keypair();

    MESSAGE("3. Starting signing example for Elliptic-curve Digital Signature Algorithm (ECDSA)");
    MESSAGE("1 Step: Sign prepared Data and export the signature");
    example_optiga_crypt_ecdsa_sign();

    MESSAGE("4. Starting verification example for Elliptic-curve Digital Signature Algorithm (ECDSA)");
    MESSAGE("1 Step: Verify prepared signature, with prepared public key and digest");
    example_optiga_crypt_ecdsa_verify();

    MESSAGE("5. Starting Elliptic-curve Diffie–Hellman (ECDH) Key Agreement Protocol Example");
    MESSAGE("1 Step: Select Protected I2C Connection");
    MESSAGE("2 Step: Generate new ECC NIST P-256 Key Pair");
    MESSAGE("3 Step: Select Protected I2C Connection");
    MESSAGE("4 Step: Generate Shared Secret and export it");
    example_optiga_crypt_ecdh();

    MESSAGE("6. Starting Generate Random Example");
    MESSAGE("1 Step: Generate 32 bytes random");
    example_optiga_crypt_random();

    MESSAGE("7. Starting TLS PRF SHA256 (Key Deriviation) Example");
    MESSAGE("1 Step: Write prepared Shared Secret into an Arbitrary Data Object");
    MESSAGE("2 Step: Update Metadata of the Object to use the Arbitrary Data Object only via Shielded I2C Connection");
    MESSAGE("3 Step: Generate Shared Secret using the Shared Secret from the Arbitrary Data Object");
    MESSAGE("4 Step: Restore Metadata of the Arbitrary Data Object");
    example_optiga_crypt_tls_prf_sha256();

    MESSAGE("8. Starting generate RSA Key Example");
    MESSAGE("1 Step: Generate RSA 1024 Key Pair and export the public key");
    example_optiga_crypt_rsa_generate_keypair();

    MESSAGE("9. Starting signing example for PKCS#1 Ver1.5 SHA256 Signature scheme (RSA)");
    MESSAGE("1 Step: Sign prepared Data and export the signature");
    example_optiga_crypt_rsa_sign();

    MESSAGE("10. Starting signing example for PKCS#1 Ver1.5 SHA256 Signature scheme (RSA)");
    MESSAGE("1 Step: Verify prepared signature, with prepared public key and digest");
    example_optiga_crypt_rsa_verify();

    MESSAGE("11. Starting Decrypt and Export Data with RSA Key Example");
    MESSAGE("1 Step: Generate RSA 1024 Key Pair and export the public key");
    MESSAGE("2 Step: Encrypt a message with RSAES PKCS#1 Ver1.5 Scheme");
    MESSAGE("3 Step: Select Protected I2C Connection");
    MESSAGE("4 Step: Decrypt the message with RSAES PKCS#1 Ver1.5 Scheme and export it");
    example_optiga_crypt_rsa_decrypt_and_export();

    MESSAGE("12. Starting Decrypt and Store Data on the chip with RSA Key Example");
    MESSAGE("1 Step: Generate RSA 1024 Key Pair and export the public key");
    MESSAGE("2 Step: Generate 70 bytes RSA Pre master secret which is stored in acquired session OID");
    MESSAGE("3 Step: Select Protected I2C Connection");
    MESSAGE("4 Step: Encrypt Session Data with RSA Public Key");
    MESSAGE("5 Step: Decrypt the message with RSAES PKCS#1 Ver1.5 Scheme and store it on chip");
    example_optiga_crypt_rsa_decrypt_and_store();

    MESSAGE("13. Starting Encrypt Data with RSA Key Example");
    MESSAGE("1 Step: Encrypt a message with RSAES PKCS#1 Ver1.5 Scheme");
    example_optiga_crypt_rsa_encrypt_message();

    MESSAGE("14. Starting Encrypt Data in Session Object on chip with RSA Key Example");
    MESSAGE("1 Step: Encrypt a message with RSAES PKCS#1 Ver1.5 Scheme stored on chip in Session Object");
    example_optiga_crypt_rsa_encrypt_session();

    MESSAGE("15. Starting symmetric Encrypt and Decrypt Data for ECB mode Example");
    MESSAGE("1 Step: Generate and store the AES 128 Symmetric key in OPTIGA Key store OID(E200)");
    MESSAGE("2 Step: Encrypt the plain data with ECB mode");
    MESSAGE("3 Step: Decrypt the encrypted data from step 2");
    example_optiga_crypt_symmetric_encrypt_decrypt_ecb();

    MESSAGE("16. Starting symmetric Encrypt and Decrypt Data for CBC mode Example");
    MESSAGE("1 Step: Generate and store the AES 128 Symmetric key in OPTIGA Key store OID(E200)");
    MESSAGE("2 Step: Encrypt the plain data with CBC mode");
    MESSAGE("3 Step: Decrypt the encrypted data from step 2");
    example_optiga_crypt_symmetric_encrypt_decrypt_cbc();

    MESSAGE("17. Starting symmetric Encrypt Data for CBCMAC mode Example");
    MESSAGE("1 Step: Generate and store the AES 128 Symmetric key in OPTIGA Key store OID(E200)");
    MESSAGE("2 Step: Encrypt the plain data with CBCMAC mode");
    example_optiga_crypt_symmetric_encrypt_cbcmac();

    MESSAGE("18. Starting HMAC-SHA256 generation Example");
    MESSAGE("1 Step: Change metadata for OID(0xF1D0) as Execute access condition = Always and Data object type  =  Pre-shared secret");
    MESSAGE("2 Step: Generate HMAC");
    example_optiga_crypt_hmac();

    MESSAGE("19. Starting HKDF-SHA256 key derivation Example");
    MESSAGE("1 Step: Write the shared secret to the Arbitrary data object F1D0");
    MESSAGE("2 Step: Change metadata of OID(0xF1D0) Data object type = Pre-shared secret");
    MESSAGE("3 Step: Derive HKDF");
    example_optiga_crypt_hkdf();

    MESSAGE("20. Starting generation of symmetric AES-128 key");
    MESSAGE("1 Step: Generate symmetric AES-128 key and store it in OID(E200)");
    example_optiga_crypt_symmetric_generate_key();

    MESSAGE("21. Starting HMAC verify with authorization reference Example");
    MESSAGE("1 Step: Get the User Secret and store it in OID(0xF1D0)");
    MESSAGE("2 Step: Set the metadata of 0xF1E0 to Auto with 0xF1D0");
    MESSAGE("3 Step: Generate authorization code with optional data");
    MESSAGE("4 Step: Calculate HMAC on host using mbedtls");
    MESSAGE("5 Step: Perform HMAC verification");
    example_optiga_hmac_verify_with_authorization_reference();

    MESSAGE("22. Starting clear auto state Example");
    MESSAGE("1 Step: Change metadata of OID(0xF1D0) Data object type = Pre-shared secret");
    MESSAGE("2 Step: Get the User Secret and store it in OID(0xF1D0)");
    MESSAGE("3 Step: Generate auth code with optional data");
    MESSAGE("4 Step: Calculate HMAC on host using mbedtls");
    MESSAGE("5 Step: Perform HMAC verification");
    MESSAGE("6 Step: Perform clear auto state");
    example_optiga_crypt_clear_auto_state();

    /*
      De-Initialise the chip with this function. Optional.
    */
    example_optiga_deinit();

    printf("****************** End of the Example ****************** \r\n\n");
}

/* [] END OF FILE */
