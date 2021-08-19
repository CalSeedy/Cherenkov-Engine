import os
import subprocess
import platform
  
from setupPython import PythonConfiguration as PythonRequirements
# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from setupPremake import PremakeConfiguration as PremakeRequirements
from setupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./../') # Change from devtools/scripts directory to root

premakeInstalled = PremakeRequirements.Validate()
VulkanRequirements.Validate()

if (premakeInstalled):
    if platform.system() == "Windows":
        print("\nRunning premake...")
        subprocess.call([os.path.abspath("./GenProjects.bat"), "nopause"])

    print("\nSetup completed!")
else:
    print("Cherenkov requires Premake to generate project files.")
