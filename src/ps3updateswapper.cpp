#include <iostream>
#include <filesystem>
#include <fstream>
#include <cerrno>

#define PS3_HFW_UPDATE_FILE "HFW_PS3UPDAT.PUP"
#define PS3_OFW_UPDATE_FILE "OFW_PS3UPDAT.PUP"
#define PS3_ACTIVE_UPDATE_FILE "PS3UPDAT.PUP"

#define HFW_INDICATOR_FILE "Current-is-HFW"
#define OFW_INDICATOR_FILE "Current-is-OFW"

namespace fs = std::filesystem;

enum FirmwareType {
    OFW = 0,
    HFW = 1
};

int main() {
    bool fileExists;
    FirmwareType replace;

    if (((!fs::exists(PS3_OFW_UPDATE_FILE) && !fs::exists(OFW_INDICATOR_FILE)) ||
        (!fs::exists(PS3_HFW_UPDATE_FILE) && !fs::exists(HFW_INDICATOR_FILE)) &&
        !(!fs::exists(PS3_ACTIVE_UPDATE_FILE) && !fs::exists(HFW_INDICATOR_FILE) && !fs::exists(OFW_INDICATOR_FILE))) ||
        (!fs::exists(PS3_HFW_UPDATE_FILE) && !fs::exists(PS3_OFW_UPDATE_FILE))) {
        std::cout << "Error: Missing file(s):" << std::endl;
        std::cout << PS3_OFW_UPDATE_FILE << ": " << (fs::exists(PS3_OFW_UPDATE_FILE) ? "Found" : "Missing") << std::endl;
        std::cout << PS3_HFW_UPDATE_FILE << ": " << (fs::exists(PS3_HFW_UPDATE_FILE) ? "Found" : "Missing") << std::endl;
        std::cout << PS3_ACTIVE_UPDATE_FILE << ": " << (fs::exists(PS3_ACTIVE_UPDATE_FILE) ? "Found" : "Missing") << std::endl;
        return ENOENT;
    }
    if (fs::exists(OFW_INDICATOR_FILE)) {
        replace = HFW;
    } else {
        replace = OFW;
    }
    switch (replace)
    {
    case HFW:
        fs::rename(OFW_INDICATOR_FILE, HFW_INDICATOR_FILE);
        if (fs::exists(PS3_ACTIVE_UPDATE_FILE) && !fs::exists(PS3_OFW_UPDATE_FILE))
            fs::rename(PS3_ACTIVE_UPDATE_FILE, PS3_OFW_UPDATE_FILE);
        else if (fs::exists(PS3_ACTIVE_UPDATE_FILE) && fs::exists(PS3_OFW_UPDATE_FILE))
            fs::remove(PS3_ACTIVE_UPDATE_FILE);
        fs::rename(PS3_HFW_UPDATE_FILE, PS3_ACTIVE_UPDATE_FILE);
        break;
    default:
        if (!fs::exists(HFW_INDICATOR_FILE)) {
                std::ofstream(OFW_INDICATOR_FILE) << "\"This one's empty.\"";
        } else {
            fs::rename(HFW_INDICATOR_FILE,OFW_INDICATOR_FILE);
        }
        if (fs::exists(PS3_ACTIVE_UPDATE_FILE) && !fs::exists(PS3_HFW_UPDATE_FILE))
            fs::rename(PS3_ACTIVE_UPDATE_FILE, PS3_HFW_UPDATE_FILE);
        else if (fs::exists(PS3_ACTIVE_UPDATE_FILE) && fs::exists(PS3_HFW_UPDATE_FILE))
            fs::remove(PS3_ACTIVE_UPDATE_FILE);
        fs::rename(PS3_OFW_UPDATE_FILE, PS3_ACTIVE_UPDATE_FILE);
        break;
    }
    return 0;
}