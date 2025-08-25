# FluxEngine CI/CD Documentation

This document describes the Continuous Integration and Continuous Deployment (CI/CD) setup for FluxEngine.

## Overview

The CI/CD pipeline is designed to:
- Build and test FluxEngine on Linux, macOS, and Windows
- Install and configure Vulkan SDK on all platforms
- Run comprehensive tests including unit tests and executable verification
- Perform static analysis and security scanning
- Create releases with cross-platform binaries
- Deploy development builds automatically

## Workflow Structure

### Main CI/CD Pipeline (`.github/workflows/ci-cd.yml`)

The pipeline consists of several jobs:

#### 1. Build and Test (`build-and-test`)
- **Platforms**: Ubuntu 22.04, macOS 13, Windows 2022
- **Compilers**: Clang (version 15 on Linux, latest on macOS/Windows)
- **Build System**: CMake + Ninja
- **Build Type**: Release
- **Vulkan SDK**: 1.3.290.0 (cached for performance)

**Steps:**
1. Checkout repository with submodules
2. Cache Vulkan SDK installation
3. Install platform-specific dependencies
4. Install Vulkan SDK if not cached
5. Configure CMake with Ninja generator
6. Build all targets (Engine, Sandbox, Studio, testGame, Tests)
7. Verify build outputs exist
8. Run unit tests with CTest
9. Test executables with basic functionality
10. Upload build artifacts

#### 2. Static Analysis (`static-analysis`)
- **Platform**: Ubuntu 22.04
- **Tools**: clang-tidy, cppcheck
- **Triggers**: Pull requests only
- **Configuration**: Uses `.clang-tidy` config file

#### 3. Security Scan (`security-scan`)
- **Platform**: Ubuntu 22.04
- **Tool**: GitHub CodeQL
- **Language**: C++
- **Triggers**: All pushes and pull requests

#### 4. Deploy Release (`deploy`)
- **Platform**: Ubuntu 22.04
- **Triggers**: Tags starting with 'v' (e.g., v1.0.0)
- **Artifacts**: Cross-platform ZIP files
- **Creates**: GitHub Release with downloadable binaries

#### 5. Deploy Development (`deploy-dev`)
- **Platform**: Ubuntu 22.04
- **Triggers**: Pushes to master branch
- **Purpose**: Development environment deployment

## Platform-Specific Configurations

### Linux (Ubuntu 22.04)
```yaml
Dependencies:
  - clang-15
  - libc++-15-dev
  - libc++abi-15-dev
  - cmake
  - ninja-build
  - libwayland-dev
  - libxrandr-dev
  - libxinerama-dev
  - libxcursor-dev
  - libxi-dev
  - libxext-dev
  - libxfixes-dev

Vulkan SDK:
  - Download from LunarG
  - Extract to runner temp directory
  - Set VULKAN_SDK environment variable
  - Add to PATH
```

### macOS (macOS 13)
```yaml
Dependencies:
  - cmake (via Homebrew)
  - ninja (via Homebrew)

Vulkan SDK:
  - Download DMG from LunarG
  - Mount and copy to ~/.vulkan-sdk
  - Set VULKAN_SDK and DYLD_LIBRARY_PATH
  - Add to PATH
```

### Windows (Windows 2022)
```yaml
Dependencies:
  - ninja (via Chocolatey)
  - Visual Studio Build Tools (pre-installed)

Vulkan SDK:
  - Download installer from LunarG
  - Silent installation to C:\VulkanSDK
  - Set VULKAN_SDK environment variable
  - Add to PATH
```

## Local Testing

Before pushing changes, you can test locally using the provided scripts:

### Windows PowerShell
```powershell
# Basic test
.\scripts\local-ci-test.ps1

# Full test with static analysis
.\scripts\local-ci-test.ps1 -RunStaticAnalysis -BuildType Debug

# Clean build
.\scripts\local-ci-test.ps1 -Clean
```

### Linux/macOS Bash
```bash
# Basic test
./scripts/local-ci-test.sh

# Full test with static analysis
./scripts/local-ci-test.sh --static-analysis --build-type Debug

# Clean build
./scripts/local-ci-test.sh --clean
```

## Troubleshooting

### Common Issues

#### 1. Vulkan SDK Not Found
**Error**: `Vulkan SDK not found` or `vulkan/vulkan.h not found`

**Solutions**:
- Verify VULKAN_SDK environment variable is set
- Check PATH includes Vulkan SDK bin directory
- Ensure Vulkan SDK version matches pipeline configuration

#### 2. Build Failures on Specific Platforms
**Error**: Compilation or linking errors on one platform

**Solutions**:
- Check platform-specific dependencies are installed
- Verify compiler versions match CI configuration
- Review CMake configuration for platform-specific settings

#### 3. Test Failures
**Error**: Unit tests or executable tests fail

**Solutions**:
- Run tests locally with verbose output: `ctest --output-on-failure --verbose`
- Check for headless environment issues (graphics/display)
- Verify all dependencies are properly linked

#### 4. Cache Issues
**Error**: Outdated dependencies or Vulkan SDK

**Solutions**:
- Clear GitHub Actions cache for the repository
- Update cache keys in workflow file
- Force fresh installation by modifying workflow

### Debug Information

The pipeline provides extensive logging:
- CMake configuration output
- Build process with parallel jobs
- Test execution with verbose output
- File verification steps
- Artifact upload confirmation

## Security Considerations

### Secrets Management
- No secrets currently required for basic CI/CD
- Future deployment may require:
  - `DEPLOYMENT_TOKEN` for server access
  - `REGISTRY_PASSWORD` for container registries
  - `SIGNING_KEY` for code signing

### Permissions
- Repository read/write access for artifact uploads
- No external service access required
- All downloads from trusted sources (LunarG, official repositories)

## Performance Optimization

### Caching Strategy
- **Vulkan SDK**: Cached per platform and version
- **Dependencies**: Package managers handle caching
- **Build artifacts**: Uploaded for 30-day retention

### Parallel Execution
- **Build**: CMake parallel jobs (all cores)
- **Tests**: CTest parallel execution (4 jobs)
- **Matrix**: All platforms run simultaneously

### Resource Usage
- **Linux**: Standard GitHub runner (2 cores, 7GB RAM)
- **macOS**: Standard GitHub runner (3 cores, 14GB RAM)  
- **Windows**: Standard GitHub runner (2 cores, 7GB RAM)

## Extending the Pipeline

### Adding New Platforms
1. Add to strategy matrix in workflow
2. Define platform-specific dependency installation
3. Configure Vulkan SDK installation for platform
4. Test locally with similar environment

### Adding New Tools
1. Install in platform-specific dependency step
2. Add execution step after build verification
3. Configure tool-specific settings
4. Handle failures appropriately (error vs warning)

### Adding Deployment Targets
1. Create new job with appropriate dependencies
2. Add required secrets to repository
3. Configure deployment scripts
4. Test in development environment first

## Monitoring and Maintenance

### Regular Tasks
- **Monthly**: Update Vulkan SDK version
- **Quarterly**: Update runner OS versions
- **Annually**: Review and update dependencies

### Metrics to Monitor
- Build success rate per platform
- Test execution time trends
- Cache hit rates
- Artifact download counts

### Alerting
- GitHub notifications for failed builds
- Email notifications for security alerts
- Dependency vulnerability alerts via Dependabot

## Support

For CI/CD related issues:
1. Check this documentation first
2. Review recent workflow runs in GitHub Actions
3. Compare with working previous runs
4. Create issue with "CI/CD" label if problem persists

Include in issue reports:
- Platform affected (Linux/macOS/Windows)
- Build logs from failed run
- Local reproduction steps attempted
- Environment differences from CI
