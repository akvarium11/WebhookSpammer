# WebhookSpammer

Simple Discord webhook message sender (C++ + libcurl).

## Building

### Prerequisites

- Visual Studio 2022 (v143 toolset) with C++ desktop development workload
- vcpkg (https://github.com/microsoft/vcpkg) - install and add to PATH

### One-time setup

```pwsh
# From the project directory
vcpkg install --triplet x64-windows-static-md
```

This installs a **statically linked** curl (using Windows Schannel for TLS).  
No runtime DLLs for curl or its dependencies are required.

### Build the project

Open `StupidAssApp.sln` (or the .vcxproj) in Visual Studio and build **Release | x64**.

The resulting executable (`WebhookSpammer.exe` or `StupidAssApp.exe` depending on rename) is portable:
- It can run from any directory
- It has no dependency on libcurl.dll or other vcpkg DLLs
- Only requires the Visual C++ Redistributable (or link CRT statically if desired)

## Usage

```text
WebhookSpammer.exe --webhook <url> --content "Hello from the void" --user "Bot" --avatar <url>
```

All parameters are also prompted interactively if missing.

## Notes

- The project uses vcpkg manifest mode (`vcpkg.json`) for reproducible dependencies.
- Static linking of curl is configured for the x64 Release and Debug configurations via MSBuild properties.
- If you move the project or use a different vcpkg root, update `VcpkgInstalledRoot` in the .vcxproj or set the `VCPKG_INSTALLED_DIR` / `VCPKG_ROOT` environment variables.
