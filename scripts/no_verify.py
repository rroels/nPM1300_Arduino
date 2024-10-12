Import("env")

old_flags = env["UPLOADERFLAGS"]
# filter out the --verify
new_flags = [opt for opt in old_flags if opt != "--verify"]
# replace and update
env.Replace(
    UPLOADERFLAGS=new_flags,
    UPLOADCMD="$UPLOADER $UPLOADERFLAGS $SOURCES"
)