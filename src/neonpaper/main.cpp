#include <iostream>
#include <string_view>

namespace {

constexpr std::string_view kProgramName{"neonpaper"};
constexpr std::string_view kVersion{NEONPAPER_VERSION};

void print_help() {
    std::cout << "NeonPaper " << kVersion << '\n'
              << "Wayland-native dynamic wallpaper daemon for Hyprland.\n\n"
              << "Usage:\n"
              << "  " << kProgramName << " [--help] [--version]\n\n"
              << "Options:\n"
              << "  --help     Show this help message.\n"
              << "  --version  Print the daemon version.\n";
}

void print_version() {
    std::cout << "NeonPaper " << kVersion << '\n';
}

} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }

    const std::string_view argument{argv[1]};
    if (argc == 2 && argument == "--help") {
        print_help();
        return 0;
    }

    if (argc == 2 && argument == "--version") {
        print_version();
        return 0;
    }

    std::cerr << "neonpaper: unsupported arguments. Try --help.\n";
    return 2;
}
