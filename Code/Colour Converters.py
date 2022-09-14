class colour_converters:
    def cmyk_to_rgb(cyan, magenta, yellow, black_key):      #Input cyan, magenta, yellow and black key as values from 0 to 1
        red = 255*(1-cyan)*(1-black_key)
        green = 255*(1-magenta)*(1-black_key)
        blue = 255*(1-yellow)*(1-black_key)
        return red, green, blue

    def rgb_to_cmyk(red, green, blue):      #Input red, green and blue as values from 0 to 255
        red /=255
        green /= 255
        blue /= 255
        rgb_list = [red, green, blue]
        rgb_list.sort()
        black_key = 1 - rgb_list[2]
        cyan = (1-red-black_key)/(1-black_key)
        magenta = (1-green-black_key)/(1-black_key)
        yellow = (1-blue-black_key)/(1-black_key)
        return cyan, magenta, yellow, black_key
        
    def rgb_to_hsl(red, green, blue):       #Input red, green and blue values from 0 to 255
        red /= 255
        green /= 255
        blue /= 255
        rgb_list = [red, green, blue]
        rgb_list.sort()
        luminance = round((rgb_list[0] + rgb_list[2])/2, 2)
        if rgb_list[0] == rgb_list[2]:
            saturation = 0
        else:
            if luminance <= 0.5:
                saturation = (rgb_list[2]-rgb_list[0])/(rgb_list[2]+rgb_list[0])
            else:
                saturation = (rgb_list[2]-rgb_list[0])/(2.0-rgb_list[2]-rgb_list[0])
        print(str(saturation))
        saturation = round(saturation, 2)
        if saturation == 0:
            hue = 0
        else:
            if red == rgb_list[2]:
                hue = (green-blue)/(rgb_list[2]-rgb_list[0])
            elif green == rgb_list[2]:
                hue = 2.0 + (blue-red)/(rgb_list[2]-rgb_list[0])
            elif blue == rgb_list[2]:
                hue = 4.0 + (red-green)/(rgb_list[2]-rgb_list[0])
        hue *= 60
        hue = round(hue)
        return hue, saturation, luminance
    
    def hsl_to_rgb(hue, saturation, luminance):     #Input hue value in degrees(360), saturation and luminance as values from 0 to 1
        if saturation == 0:
            red  = luminance * 255
            green = luminance * 255
            blue = luminance * 255
            return red, green, blue
        if luminance < 0.5:
            temporary_1 = luminance*(1.0+saturation)
        else:
            temporary_1 = luminance + saturation - luminance * saturation
        temporary_2 = 2 * luminance - temporary_1
        hue /= 360
        temporary_rgb = [hue + 0.333, hue, hue - 0.333]
        for value in temporary_rgb:
            if value < 0:
                value += 1
            elif value > 1:
                value -= 1
        rgb = [0, 0, 0]
        for i in range(3):
            if 6*temporary_rgb[i] < 1:
                rgb[i] = temporary_2 + (temporary_1 - temporary_2) * 6 * temporary_rgb[i]
            elif 2*temporary_rgb[i] < 1:
                rgb[i] = temporary_1
            elif 3*temporary_rgb[i] < 2:
                rgb[i] = temporary_2 + (temporary_1 - temporary_2) * (0.666 - temporary_rgb[i]) * 6
            else:
                rgb[i] = temporary_2
        for value in rgb:
            value = round(value*255)
        return rgb[0], rgb[1], rgb[2]

    def rgb_to_hex(red, green, blue):                       #Input red, green and blue values from 0 to 255
        hex_value = 0
        hex_value = red*0x10000 + green*0x100 + blue
        hex_str =  str('#' + hex(hex_value))
        return hex_str.replace('0x', '')

    def hex_to_rgb(hex_value):          #Input a string with a hex value(# then 6-digit hexadecimal value)
        red = '0x' + hex_value[1:3]
        green = '0x' + hex_value[3:5]
        blue = '0x' + hex_value[5:7]
        return int(red, 16), int(green, 16), int(blue, 16)











            

