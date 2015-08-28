
#include <media/stagefright/foundation/ABase.h>
#include <media/stagefright/foundation/AString.h>
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>

namespace android {

struct Parameters : public RefBase {
    static sp<Parameters> Parse(const char *data, size_t size);

    bool findParameter(const char *name, AString *value) const;

protected:
    virtual ~Parameters();

private:
    KeyedVector<AString, AString> mDict;

    Parameters();
    status_t parse(const char *data, size_t size);

    DISALLOW_EVIL_CONSTRUCTORS(Parameters);
};

}  // namespace android
