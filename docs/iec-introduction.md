## ForgeRock Identity Edge Controller Introduction

The Identity Edge Controller (IEC) consists of multiple components that together enable devices to securely register as identities in AM. Once registered, the IEC enables a device to:

* Get configuration.
* Request OAuth2 access and ID tokens.
* Allow devices to pair with users using OAuth2 Device Flow.
* Call customisable scripts in AM.

The IEC consists of four components:

* The IEC SDK client library provides a simple C API for client applications to invoke AM functionality via the IEC Service. The IEC SDK library is small and uses a secure lightweight messaging protocol so that it can run on constrained devices.
* The IEC Service runs on a device on the local network, providing secure communications between client applications and AM. Additionally, there is an ARM TrustZone enabled version of the IEC Service that provides secure storage on devices that support OP-TEE.
* The IEC AM Plugin adds IoT specific functionality to AM. It provides a single secure communication point for the IEC Service and allows the IEC Service to perform tasks like registering edge nodes and retrieving OAuth2 tokens.
* The Edge Identity Manager provides a User Interface to AM for viewing and managing device identities.

![IEC components](images/IEC-Components.png "IEC Components")

## IEC Edge Architecture
The IEC implements a hierarchy of nodes at the edge, typically devices running embedded software. The edge nodes are 
physical or virtual things that exist at the edge and benefit from having an identity. The nodes can range
from fully capable nodes that can securely connect across a wide-area network to more constrained nodes. The IEC
has three edge node types: IEC, CLIENT and DEVICE. The type is stored in the edge node’s identity and is
used to make decisions about the edge node functions and properties.

![IEC Edge Node Types](images/IEC-Edge-Node-Types.png "IEC Edge Node Types")

* The IEC edge node type represents an IEC Service and has a one to many relationship with CLIENT edge nodes.
* The CLIENT edge node type represents a client application that makes use of the IEC SDK and has a one to many
relationship with DEVICE edge nodes.
* The DEVICE edge node type represents a physical device that can be onboarded via the IEC SDK.
