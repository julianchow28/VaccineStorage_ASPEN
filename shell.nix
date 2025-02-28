{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell rec {
  buildInputs = [
    # pkgs.arduino
    pkgs.arduino-ide
    pkgs.arduino
    pkgs.arduino-cli  # Arduino CLI for compiling/uploading sketches
    pkgs.pkgsCross.avr.buildPackages.gcc  # AVR GCC toolchain
    pkgs.pkgsCross.avr.libcCross  # Standard C library for AVR
    pkgs.pkgsCross.avr.buildPackages.avrdude  # Flashing tool for AVR microcontrollers
    pkgs.picocom  # Serial monitor (alternative: minicom, screen)
  ];

  shellHook = ''
    echo "Arduino development environment loaded!"
    echo "Run 'arduino-cli board list' to check connected devices."
    
    # Check if the Arduino AVR core is installed, and install it if necessary
    if ! arduino-cli core list | grep -q "arduino:avr"; then
      echo "Installing Arduino AVR core..."
      arduino-cli core install arduino:avr
    else
      echo "Arduino AVR core is already installed."
    fi
  '';
}
