#import <Cocoa/Cocoa.h>

#import "ProfileModel.h"

extern NSString *const kCustomColorPresetsKey;
extern NSString *const kRebuildColorPresetsMenuNotification;

@class Profile;
@class ProfileModel;

// Values are numbers for components or a string for the color space
typedef NSDictionary<NSString *, id> iTermColorDictionary;
typedef NSDictionary<NSString *, iTermColorDictionary *> iTermColorPreset;
typedef NSDictionary<NSString *, iTermColorPreset *> iTermColorPresetDictionary;

// This is a model for the color presets that are globally loaded into user defaults. It also
// provides convenience methods for accessing and modifying profiles, exporting profiles, getting a
// color from a preset, and getting the collection of color keys used in a preset.
@interface iTermColorPresets : NSObject

// Loaded presets
+ (iTermColorPresetDictionary *)customColorPresets;

// Factory-supplied presets
+ (iTermColorPresetDictionary *)builtInColorPresets;

// Both loaded and builtin
+ (iTermColorPresetDictionary *)allColorPresets;

// Loook up a loaded preset by name
+ (iTermColorPreset *)presetWithName:(NSString *)presetName;

// Load a preset
+ (BOOL)importColorPresetFromFile:(NSString *)filename;

// Remove a loaded preset
+ (void)deletePresetWithName:(NSString *)name;

@end

@interface NSDictionary(iTermColorPreset)

// Extract a preset from a profile
- (iTermColorDictionary *)iterm_presetColorWithName:(NSString *)colorName;

// Save a preset to disk
- (BOOL)iterm_writePresetToFileWithName:(NSString *)filename;

@end

@interface ProfileModel(iTermColorPresets)

// Keys in a preset dictionary
+ (NSArray<NSString *> *)colorKeysWithModes:(BOOL)modes;

// Add a loaded preset to a profile
// dark = nil: Update all modes
// dark = @YES: Update dark mode
// dark = @NO: Update light mode
- (BOOL)addColorPresetNamed:(NSString *)presetName toProfile:(Profile *)profile dark:(NSNumber *)dark;

@end

BOOL iTermColorPresetHasModes(iTermColorPreset *preset);
NSColor *iTermColorPresetGet(iTermColorPreset *preset, NSString *baseKey, BOOL dark);

