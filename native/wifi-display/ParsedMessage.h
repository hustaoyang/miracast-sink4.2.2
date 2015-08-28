
#include <media/stagefright/foundation/ABase.h>
#include <media/stagefright/foundation/AString.h>
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>

namespace android {

// Encapsulates an "HTTP/RTSP style" response, i.e. a status line,
// key/value pairs making up the headers and an optional body/content.
struct ParsedMessage : public RefBase {
    static sp<ParsedMessage> Parse(
            const char *data, size_t size, bool noMoreData, size_t *length);

    bool findString(const char *name, AString *value) const;
    bool findInt32(const char *name, int32_t *value) const;

    const char *getContent() const;

    void getRequestField(size_t index, AString *field) const;
    bool getStatusCode(int32_t *statusCode) const;

    AString debugString() const;

    static bool GetAttribute(const char *s, const char *key, AString *value);

    static bool GetInt32Attribute(
            const char *s, const char *key, int32_t *value);


protected:
    virtual ~ParsedMessage();

private:
    KeyedVector<AString, AString> mDict;
    AString mContent;

    ParsedMessage();

    ssize_t parse(const char *data, size_t size, bool noMoreData);

    DISALLOW_EVIL_CONSTRUCTORS(ParsedMessage);
};

}  // namespace android
