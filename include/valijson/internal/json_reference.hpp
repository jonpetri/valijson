#ifndef __VALIJSON_INTERNAL_JSON_REFERENCE_HPP
#define __VALIJSON_INTERNAL_JSON_REFERENCE_HPP

#include <stdexcept>
#include <string>

#include <boost/optional.hpp>

namespace valijson {
namespace internal {
namespace json_reference {

    /**
     * @brief   Extract URI from JSON Reference relative to the current schema
     *
     * @param   jsonRef  JSON Reference to extract from
     * @param   schema   Schema that JSON Reference URI is relative to
     *
     * @return  Optional string containing URI
     */
    inline boost::optional<std::string> getJsonReferenceUri(
        const std::string &jsonRef)
    {
        const size_t ptrPos = jsonRef.find("#");
        if (ptrPos == 0) {
            // The JSON Reference does not contain a URI, but might contain a
            // JSON Pointer that refers to the current document
            return boost::none;
        } else if (ptrPos != std::string::npos) {
            // The JSON Reference contains a URI and possibly a JSON Pointer
            return jsonRef.substr(0, ptrPos);
        }

        // The entire JSON Reference should be treated as a URI
        return jsonRef;
    }

    /**
     * @brief   Extract JSON Pointer portion of a JSON Reference
     *
     * @param   jsonRef  JSON Reference to extract from
     *
     * @return  string containing JSON Pointer
     *
     * @throw   std::runtime_error if the string does not contain a JSON Pointer
     */
    inline std::string getJsonReferencePointer(const std::string &jsonRef)
    {
        // Attempt to extract JSON Pointer if '#' character is present. Note
        // that a valid pointer would contain at least a leading forward
        // slash character.
        const size_t ptrPos = jsonRef.find("#");
        if (ptrPos != std::string::npos) {
            return jsonRef.substr(ptrPos + 1);
        }

        throw std::runtime_error(
                "JSON Reference value does not contain a valid JSON Pointer");
    }

} // namespace json_reference
} // namespace internal
} // namespace valijson

#endif