Here's the complete README content in markdown format to copy and add to your GitHub project repository:

```markdown
# Contact Manager Application

This is a simple C-based contact manager application for Windows using the Win32 API. The application allows users to add, view, and remove contacts. It stores contact information (name, phone, and email) in a text file, providing persistent data storage across application launches.

## Features

- **Add Contacts**: Users can add new contacts by providing their name, phone number, and email.
- **View Contacts**: Users can view all stored contacts in the list format.
- **Remove Contacts**: Users can remove contacts from the list by providing the contact's index.
- **Persistent Storage**: Contacts are saved to and loaded from a `contacts.txt` file, so the data persists even after closing the application.

## Prerequisites

- Windows operating system.
- A C compiler (e.g., GCC, MSVC) that supports the Windows API.

## Setup and Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/deman404/contact-manager.git
   ```

2. Open the project in your favorite C development environment (e.g., Visual Studio, Code::Blocks, or MinGW with GCC).

3. Compile and build the application:
   - If using **GCC**, use the following command in your terminal (after navigating to the project folder):
     ```bash
     gcc -o ContactManager.exe main.c -lcomdlg32 -lgdi32
     ```

   - If using **Visual Studio**, open the `.vcxproj` file and build the project.

4. Run the compiled `ContactManager.exe` on your Windows machine.

## Usage

Once the application is running, you will see the following UI elements:

- **Name**: A text field where you can input the name of a contact.
- **Phone**: A text field for entering the phone number of the contact.
- **Email**: A text field for entering the email address of the contact.
- **Add Contact**: A button to add the entered contact information to the list.
- **Show Contacts**: A button to display all saved contacts.
- **Remove Contact**: A text field and a button to remove a contact by specifying its index in the list.

### Contact Format in File:
- **contacts.txt**: A text file where contacts are stored in a CSV format (Name, Phone, Email).
  Example:
  ```
  Ayman,060000000,ayman@example.com
  Ayman2,060033000,ayman2@example.com
  
  ```

## Screenshots

(Here you can include some screenshots of the app UI or provide a link to a GIF showing the application in action.)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

If you would like to contribute to this project, feel free to fork the repository and submit pull requests. Issues and feature requests are also welcome.

## Authors

- **Ayman Azhar** - _Initial work_ - [Your GitHub Profile](https://github.com/deman404)

## Acknowledgments

- Windows API for creating the UI and managing the application.
- `fopen` and `fscanf` for reading and writing to a file.
- Community and open-source projects that made developing this application easier.

---
