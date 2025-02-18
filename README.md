# Jelly Anime Title Optimizer

A simple command-line tool that automatically renames anime episodes to a format compatible with media servers. Powered by ChatGPT, it extracts episode metadata and generates proper episode titles.

## Installation

1. Download the latest release for your platform:
   - `anime-renamer-macos` for MacOS
   - `anime-renamer.exe` for Windows (compile from source)

2. Make the file executable (MacOS only):
   ```bash
   chmod +x anime-renamer-macos
   ```

## Usage

1. Copy the `anime-renamer` executable into the folder containing your anime episodes

2. Run the executable:
   - MacOS: Double-click `anime-renamer-macos` or run via terminal
   - Windows: Double-click `anime-renamer.exe`

3. First-time setup:
   - You'll be prompted to enter your OpenAI API key
   - The key will be saved to `apikey.txt` in the same directory
   - For future uses, just copy both the executable and `apikey.txt` to any folder you want to rename

4. The program will:
   - Scan for video files
   - Show you a preview of the proposed changes
   - Ask for confirmation before renaming

## API Key Information

- I reccomend using gpt-4o-mini because it's functional and cheap.
- API key is stored locally in `apikey.txt`
- You can easily use the tool in multiple folders by copying both the executable and `apikey.txt`

## Compatibility

- Tested primarily on MacOS
- Should work on Windows when compiled
- Supports major video formats: .mkv, .mp4, .avi, .mov
- Output format compatible with Jellyfin, not tested for Plex but should be the same.

## File Naming Format

The tool renames files to the following format:
```
Show Name - SXXEXX - Episode Title.extension
```

Example:
```
Bocchi the Rock - S01E01 - Lonely Rolling Bocchi.mkv
```

## Safety Features

- Preview changes before applying
- Confirmation required before renaming
- Original filenames can be logged (check terminal output)

## Tips

- Place the executable in the same directory as your anime episodes
- For batch processing across multiple folders, just copy both the executable and `apikey.txt`
- The tool ignores non-video files automatically

## License

no commercial use.