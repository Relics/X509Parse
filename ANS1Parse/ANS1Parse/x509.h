#ifndef X509_H
#define X509_H

#include <time.h>
#include "huge.h"
#include "rsa.h"
#include "dsa.h"

typedef enum
{
  rsa,
  dsa,
  dh
}
algorithmIdentifier;

typedef enum
{
  md5WithRSAEncryption,
  shaWithRSAEncryption,
  shaWithDSA
}
signatureAlgorithmIdentifier;

/**
 * A name (or "distinguishedName") is a list of attribute-value pairs.
 * Instead of keeping track of all of them, just keep track of
 * the most interesting ones.
 */
typedef struct
{
  char *idAtCountryName;
  char *idAtStateOrProvinceName;
  char *idAtLocalityName;
  char *idAtOrganizationName;
  char *idAtOrganizationalUnitName;
  char *idAtCommonName;
}
name;

typedef struct
{
  // TODO deal with the "utcTime" or "GeneralizedTime" choice.
  time_t notBefore;
  time_t notAfter;
}
validity_period;

typedef huge uniqueIdentifier;

typedef struct
{
  algorithmIdentifier algorithm;
  rsa_key rsa_public_key;

  // DSA or DH parameters, only if algorithm == dsa
  dsa_params dsa_parameters;
 
  // DSA parameters, only if algorithm == dsa
  huge dsa_public_key;
} 
public_key_info;   //不一定要用联合体，用了联合体反而复杂化了。

typedef huge objectIdentifier;

typedef struct
{
  int version;
  huge serialNumber; // This can be much longer than a 4-byte long allows
  signatureAlgorithmIdentifier signature;
  name issuer;
  validity_period validity;
  name subject;
  public_key_info subjectPublicKeyInfo;
  uniqueIdentifier issuerUniqueId;
  uniqueIdentifier subjectUniqueId;
  int certificate_authority; // 1 if this is a CA, 0 if not
}
x509_certificate;

typedef struct
{
  x509_certificate tbsCertificate;
  unsigned int *hash; // hash code of tbsCertificate
  int hash_len;
  signatureAlgorithmIdentifier algorithm;
  huge rsa_signature_value;
  dsa_signature dsa_signature_value;
} 
signed_x509_certificate;



typedef struct 
{ 
  char *modulus;
  char *exponent;
  char *signValue;
}ras_info;

typedef struct 
{
  char *y;
  char *p;
  char *q;
  char *g;
  char *r;
  char *s;
}dsa_info;

typedef struct  
{
  char* version;
  char* serialnumber;
  char* issuer;
  char* subject;
  char* notbefore;
  char* notafter;
  char* algFlag;
  dsa_info ds;
  ras_info rs;
  char *signAlgorithm;
  char *caflag;
}x509Info;


void init_x509_certificate( signed_x509_certificate *certificate );
void init_x509_msg(x509Info * x509_msg);
void free_x509_msg(x509Info * x509_msg);
int parse_x509_certificate( const unsigned char *buffer,
              const unsigned int certificate_length,
              signed_x509_certificate *parsed_certificate );
void free_x509_certificate( signed_x509_certificate *certificate );
void display_x509_certificate( signed_x509_certificate *certificate, CString& str);
void display_x509(signed_x509_certificate *certificate, x509Info * x509);
int validate_certificate_rsa( signed_x509_certificate *certificate, rsa_key *public_key );
int validate_certificate_dsa( signed_x509_certificate *certificate );
#endif
