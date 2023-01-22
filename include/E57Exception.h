/*
 * Original work Copyright 2009 - 2010 Kevin Ackley (kackley@gwi.net)
 * Modified work Copyright 2018 - 2020 Andy Maloney <asmaloney@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

/// @file E57Exception.h Exception handling for E57 API.

#include <exception>
#include <iostream>
#include <string>

#include "E57Export.h"

#ifndef E57_ENABLE_DIAGNOSTIC_OUTPUT
// Used to mark unused parameters to indicate intent and supress warnings.
#define UNUSED( expr ) (void)( expr )
#endif

// C++14 does not support the [[deprecated]] attribute on enumerators.
// Turn on enumerator deprecation notices if we are compiling with C++17 or later.
#if ( ( defined( _MSVC_LANG ) && _MSVC_LANG >= 201703L ) || __cplusplus >= 201703L )
#define DEPRECATED_ENUM( str ) [[deprecated( str )]]
#else
#define DEPRECATED_ENUM( str )
#endif

namespace e57
{
   /// @brief Numeric error identifiers used in E57Exception
   enum ErrorCode
   {
      // NOTE: When changing error strings here, remember to update the error strings in
      // E57Exception.cpp

      Success = 0, ///< operation was successful

      ErrorBadCVHeader = 1,           ///< a CompressedVector binary header was bad
      ErrorBadCVPacket = 2,           ///< a CompressedVector binary packet was bad
      ErrorChildIndexOutOfBounds = 3, ///< a numerical index identifying a child was out of bounds
      ErrorSetTwice = 4,              ///< attempted to set an existing child element to a new value

      /// @brief attempted to add an element that would have made the children of a homogeneous
      /// ::TypeVector have different types
      ErrorHomogeneousViolation = 5,

      /// a value could not be represented in the requested type
      ErrorValueNotRepresentable = 6,

      /// after scaling the result could not be represented in the requested type
      ErrorScaledValueNotRepresentable = 7,

      /// a 64 bit IEEE float was too large to store in a 32 bit IEEE float
      ErrorReal64TooLarge = 8,

      /// expecting numeric representation in user's buffer, found ustring
      ErrorExpectingNumeric = 9,

      /// expecting string representation in user's buffer, found numeric
      ErrorExpectingUString = 10,

      ErrorInternal = 11,       ///< An unrecoverable inconsistent internal state was detected
      ErrorBadXMLFormat = 12,   ///< E57 primitive not encoded in XML correctly
      ErrorXMLParser = 13,      ///< XML not well formed
      ErrorBadAPIArgument = 14, ///< bad API function argument provided by user
      ErrorFileReadOnly = 15,   ///< can't modify read only file
      ErrorBadChecksum = 16,    ///< checksum mismatch, file is corrupted
      ErrorOpenFailed = 17,     ///< open() failed
      ErrorCloseFailed = 18,    ///< close() failed
      ErrorReadFailed = 19,     ///< read() failed
      ErrorWriteFailed = 20,    ///< write() failed
      ErrorSeekFailed = 21,     ///< lseek() failed
      ErrorPathUndefined = 22,  ///< element path well formed but not defined
      ErrorBadBuffer = 23,      ///< bad SourceDestBuffer

      /// no buffer specified for an element in CompressedVectorNode during write
      ErrorNoBufferForElement = 24,

      ErrorBufferSizeMismatch = 25,       ///< SourceDestBuffers not all same size
      ErrorBufferDuplicatePathName = 26,  ///< duplicate pathname in CompressedVectorNode read/write
      ErrorBadFileSignature = 27,         ///< file signature not "ASTM-E57"
      ErrorUnknownFileVersion = 28,       ///< incompatible file version
      ErrorBadFileLength = 29,            ///< size in file header not same as actual
      ErrorXMLParserInit = 30,            ///< XML parser failed to initialize
      ErrorDuplicateNamespacePrefix = 31, ///< namespace prefix already defined
      ErrorDuplicateNamespaceURI = 32,    ///< namespace URI already defined
      ErrorBadPrototype = 33,             ///< bad prototype in CompressedVectorNode
      ErrorBadCodecs = 34,                ///< bad codecs in CompressedVectorNode
      ErrorValueOutOfBounds = 35,         ///< element value out of min/max bounds

      /// conversion required to assign element value, but not requested
      ErrorConversionRequired = 36,

      ErrorBadPathName = 37,            ///< E57 path name is not well formed
      ErrorNotImplemented = 38,         ///< functionality not implemented
      ErrorBadNodeDowncast = 39,        ///< bad downcast from Node to specific node type
      ErrorWriterNotOpen = 40,          ///< CompressedVectorWriter is no longer open
      ErrorReaderNotOpen = 41,          ///< CompressedVectorReader is no longer open
      ErrorNodeUnattached = 42,         ///< node is not yet attached to tree of ImageFile
      ErrorAlreadyHasParent = 43,       ///< node already has a parent
      ErrorDifferentDestImageFile = 44, ///< nodes were constructed with different destImageFiles
      ErrorImageFileNotOpen = 45,       ///< destImageFile is no longer open

      /// SourceDestBuffers not compatible with previously given ones
      ErrorBuffersNotCompatible = 46,

      ErrorTooManyWriters = 47,      ///< too many open CompressedVectorWriters of an ImageFile
      ErrorTooManyReaders = 48,      ///< too many open CompressedVectorReaders of an ImageFile
      ErrorBadConfiguration = 49,    ///< bad configuration string
      ErrorInvarianceViolation = 50, ///< class invariance constraint violation in debug mode

      /// an invalid node type was passed in Data3D pointFields
      ErrorInvalidNodeType = 51,

      /// passed an invalid value in Data3D pointFields
      ErrorInvalidData3DValue = 52,

      /// @deprecated Will be removed in 4.0. Use e57::Success.
      E57_SUCCESS DEPRECATED_ENUM( "Will be removed in 4.0. Use Success." ) = Success,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadCVHeader.
      E57_ERROR_BAD_CV_HEADER DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadCVHeader." ) =
         ErrorBadCVHeader,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadCVPacket.
      E57_ERROR_BAD_CV_PACKET DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadCVPacket." ) =
         ErrorBadCVPacket,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorChildIndexOutOfBounds.
      E57_ERROR_CHILD_INDEX_OUT_OF_BOUNDS DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorChildIndexOutOfBounds." ) = ErrorChildIndexOutOfBounds,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorSetTwice.
      E57_ERROR_SET_TWICE DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorSetTwice." ) =
         ErrorSetTwice,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorHomogeneousViolation.
      E57_ERROR_HOMOGENEOUS_VIOLATION DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorHomogeneousViolation." ) = ErrorHomogeneousViolation,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorValueNotRepresentable.
      E57_ERROR_VALUE_NOT_REPRESENTABLE DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorValueNotRepresentable." ) = ErrorValueNotRepresentable,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorScaledValueNotRepresentable.
      E57_ERROR_SCALED_VALUE_NOT_REPRESENTABLE DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorScaledValueNotRepresentable." ) =
         ErrorScaledValueNotRepresentable,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorReal64TooLarge.
      E57_ERROR_REAL64_TOO_LARGE DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorReal64TooLarge." ) = ErrorReal64TooLarge,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorExpectingNumeric.
      E57_ERROR_EXPECTING_NUMERIC DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorExpectingNumeric." ) = ErrorExpectingNumeric,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorExpectingUString.
      E57_ERROR_EXPECTING_USTRING DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorExpectingUString." ) = ErrorExpectingUString,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorInternal.
      E57_ERROR_INTERNAL DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorInternal." ) =
         ErrorInternal,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadXMLFormat.
      E57_ERROR_BAD_XML_FORMAT DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadXMLFormat." ) =
         ErrorBadXMLFormat,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorXMLParser.
      E57_ERROR_XML_PARSER DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorXMLParser." ) =
         ErrorXMLParser,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadAPIArgument.
      E57_ERROR_BAD_API_ARGUMENT DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBadAPIArgument." ) = ErrorBadAPIArgument,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorFileReadOnly.
      E57_ERROR_FILE_IS_READ_ONLY DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorFileReadOnly." ) = ErrorFileReadOnly,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadChecksum.
      E57_ERROR_BAD_CHECKSUM DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadChecksum." ) =
         ErrorBadChecksum,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorOpenFailed.
      E57_ERROR_OPEN_FAILED DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorOpenFailed." ) =
         ErrorOpenFailed,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorCloseFailed.
      E57_ERROR_CLOSE_FAILED DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorCloseFailed." ) =
         ErrorCloseFailed,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorReadFailed.
      E57_ERROR_READ_FAILED DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorReadFailed." ) =
         ErrorReadFailed,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorWriteFailed.
      E57_ERROR_WRITE_FAILED DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorWriteFailed." ) =
         ErrorWriteFailed,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorSeekFailed.
      E57_ERROR_LSEEK_FAILED DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorSeekFailed." ) =
         ErrorSeekFailed,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorPathUndefined.
      E57_ERROR_PATH_UNDEFINED DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorPathUndefined." ) = ErrorPathUndefined,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadBuffer.
      E57_ERROR_BAD_BUFFER DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadBuffer." ) =
         ErrorBadBuffer,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorNoBufferForElement.
      E57_ERROR_NO_BUFFER_FOR_ELEMENT DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorNoBufferForElement." ) = ErrorNoBufferForElement,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBufferSizeMismatch.
      E57_ERROR_BUFFER_SIZE_MISMATCH DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBufferSizeMismatch." ) = ErrorBufferSizeMismatch,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBufferDuplicatePathName.
      E57_ERROR_BUFFER_DUPLICATE_PATHNAME DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBufferDuplicatePathName." ) =
         ErrorBufferDuplicatePathName,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadFileSignature.
      E57_ERROR_BAD_FILE_SIGNATURE DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBadFileSignature." ) = ErrorBadFileSignature,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorUnknownFileVersion.
      E57_ERROR_UNKNOWN_FILE_VERSION DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorUnknownFileVersion." ) = ErrorUnknownFileVersion,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadFileLength.
      E57_ERROR_BAD_FILE_LENGTH DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBadFileLength." ) = ErrorBadFileLength,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorXMLParserInit.
      E57_ERROR_XML_PARSER_INIT DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorXMLParserInit." ) = ErrorXMLParserInit,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorDuplicateNamespacePrefix.
      E57_ERROR_DUPLICATE_NAMESPACE_PREFIX DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorDuplicateNamespacePrefix." ) =
         ErrorDuplicateNamespacePrefix,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorDuplicateNamespaceURI.
      E57_ERROR_DUPLICATE_NAMESPACE_URI DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorDuplicateNamespaceURI." ) = ErrorDuplicateNamespaceURI,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadPrototype.
      E57_ERROR_BAD_PROTOTYPE DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadPrototype." ) =
         ErrorBadPrototype,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadCodecs.
      E57_ERROR_BAD_CODECS DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadCodecs." ) =
         ErrorBadCodecs,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorValueOutOfBounds.
      E57_ERROR_VALUE_OUT_OF_BOUNDS DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorValueOutOfBounds." ) = ErrorValueOutOfBounds,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorConversionRequired.
      E57_ERROR_CONVERSION_REQUIRED DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorConversionRequired." ) = ErrorConversionRequired,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadPathName.
      E57_ERROR_BAD_PATH_NAME DEPRECATED_ENUM( "Will be removed in 4.0. Use ErrorBadPathName." ) =
         ErrorBadPathName,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorNotImplemented.
      E57_ERROR_NOT_IMPLEMENTED DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorNotImplemented." ) = ErrorNotImplemented,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadNodeDowncast.
      E57_ERROR_BAD_NODE_DOWNCAST DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBadNodeDowncast." ) = ErrorBadNodeDowncast,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorWriterNotOpen.
      E57_ERROR_WRITER_NOT_OPEN DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorWriterNotOpen." ) = ErrorWriterNotOpen,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorReaderNotOpen.
      E57_ERROR_READER_NOT_OPEN DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorReaderNotOpen." ) = ErrorReaderNotOpen,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorNodeUnattached.
      E57_ERROR_NODE_UNATTACHED DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorNodeUnattached." ) = ErrorNodeUnattached,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorAlreadyHasParent.
      E57_ERROR_ALREADY_HAS_PARENT DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorAlreadyHasParent." ) = ErrorAlreadyHasParent,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorDifferentDestImageFile.
      E57_ERROR_DIFFERENT_DEST_IMAGEFILE DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorDifferentDestImageFile." ) = ErrorDifferentDestImageFile,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorImageFileNotOpen.
      E57_ERROR_IMAGEFILE_NOT_OPEN DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorImageFileNotOpen." ) = ErrorImageFileNotOpen,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBuffersNotCompatible.
      E57_ERROR_BUFFERS_NOT_COMPATIBLE DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBuffersNotCompatible." ) = ErrorBuffersNotCompatible,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorTooManyWriters.
      E57_ERROR_TOO_MANY_WRITERS DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorTooManyWriters." ) = ErrorTooManyWriters,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorTooManyReaders.
      E57_ERROR_TOO_MANY_READERS DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorTooManyReaders." ) = ErrorTooManyReaders,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorBadConfiguration.
      E57_ERROR_BAD_CONFIGURATION DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorBadConfiguration." ) = ErrorBadConfiguration,
      /// @deprecated Will be removed in 4.0. Use e57::ErrorInvarianceViolation.
      E57_ERROR_INVARIANCE_VIOLATION DEPRECATED_ENUM(
         "Will be removed in 4.0. Use ErrorInvarianceViolation." ) = ErrorInvarianceViolation,
   };

   namespace Utilities
   {
      E57_DLL std::string errorCodeToString( ErrorCode ecode ) noexcept;
   }

   class E57Exception : public std::exception
   {
   public:
      const char *what() const noexcept override
      {
         return "E57 exception";
      }

      void report( const char *reportingFileName = nullptr, int reportingLineNumber = 0,
                   const char *reportingFunctionName = nullptr,
                   std::ostream &os = std::cout ) const noexcept
      {
         os << "**** Got an e57 exception: " << errorStr() << std::endl;

#ifdef E57_ENABLE_DIAGNOSTIC_OUTPUT
         os << "  Debug info: " << std::endl;
         os << "    context: " << context_ << std::endl;
         os << "    sourceFunctionName: " << sourceFunctionName_ << std::endl;
         if ( reportingFunctionName != nullptr )
         {
            os << "    reportingFunctionName: " << reportingFunctionName << std::endl;
         }

         /*** Add a line in error message that a smart editor (gnu emacs) can
          * interpret as a link to the source code: */
         os << sourceFileName_ << "(" << sourceLineNumber_ << ") : error C" << errorCode_
            << ":  <--- occurred on" << std::endl;
         if ( reportingFileName != nullptr )
         {
            os << reportingFileName << "(" << reportingLineNumber
               << ") : error C0:  <--- reported on" << std::endl;
         }
#else
         UNUSED( reportingFileName );
         UNUSED( reportingLineNumber );
         UNUSED( reportingFunctionName );
#endif
      }

      ErrorCode errorCode() const noexcept
      {
         return errorCode_;
      }

      std::string errorStr() const noexcept
      {
         return Utilities::errorCodeToString( errorCode_ );
      }

      std::string context() const noexcept
      {
         return context_;
      }

      // For debugging purposes:
      const char *sourceFileName() const noexcept
      {
         return sourceFileName_.c_str();
      }

      const char *sourceFunctionName() const noexcept
      {
         return sourceFunctionName_;
      }

      int sourceLineNumber() const noexcept
      {
         return sourceLineNumber_;
      }

      /// @cond documentNonPublic The following isn't part of the API, and isn't documented.
      E57Exception() = delete;
      E57Exception( ErrorCode ecode, std::string context, const char *srcFileName = nullptr,
                    int srcLineNumber = 0, const char *srcFunctionName = nullptr ) :
         errorCode_( ecode ),
         context_( std::move( context ) ), sourceFileName_( srcFileName ),
         sourceFunctionName_( srcFunctionName ), sourceLineNumber_( srcLineNumber )
      {
      }
      /// @endcond

   private:
      /// @cond documentNonPublic The following isn't part of the API, and isn't documented.
      ErrorCode errorCode_;
      std::string context_;
      std::string sourceFileName_;
      const char *sourceFunctionName_;
      int sourceLineNumber_;
      /// @endcond
   };
}
