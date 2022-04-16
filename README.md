# test_appstream_screenshots
small example to show how screenshot URLs are parsed in libappstream

Place test metadata files in `metadata` subdirectory in current directory and run test executable.

Example output:
```
test: Pool default flags:  "FlagLoadOsCollection | FlagLoadOsMetainfo | FlagLoadFlatpak"
test: Pool new flags:  "FlagLoadOsCollection"
test: Adding extra metadata path:  "/home/lexx/dev/test/build-test_appstream-System_Qt-Debug/metadata"
test: Loaded total  1  components
test: Found ktorrent  1  times
test:    "org.kde.ktorrent.desktop"
test:      "KindSource" ; url:  "https://appstream.alpinelinux.org/media/edge/https://cdn.kde.org/screenshots/ktorrent/ktorrent.png"
test:      "KindSource" ; url:  "https://appstream.alpinelinux.org/media/edge/org/kde/ktorrent.desktop/2250ef363428df697ba6e87d1d66e821/screenshots/image-1_orig.png"
test:      "KindThumbnail" ; url:  "https://appstream.alpinelinux.org/media/edge/org/kde/ktorrent.desktop/2250ef363428df697ba6e87d1d66e821/screenshots/image-1_752x531.png"
test:      "KindThumbnail" ; url:  "https://appstream.alpinelinux.org/media/edge/org/kde/ktorrent.desktop/2250ef363428df697ba6e87d1d66e821/screenshots/image-1_624x440.png"
test:      "KindThumbnail" ; url:  "https://appstream.alpinelinux.org/media/edge/org/kde/ktorrent.desktop/2250ef363428df697ba6e87d1d66e821/screenshots/image-1_224x158.png"
```
