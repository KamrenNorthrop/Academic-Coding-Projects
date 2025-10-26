from pokedex import Pokedex
import time

def main():
    print("Welcome to Text Pokemon!\n")
    
    #Initialization of player pokedex
    pokedex = Pokedex() 
    
    #Load previous game?
    pokedex.load_game_prompt()
        
    in_progress = True
    while in_progress:
        choice = pokedex.main_menu_prompt()
        options = ["1", "2", "3", "4", "5"]

        if choice not in options:
            print("Invalid choice. Please try again.")
            continue

        #Player searches for Pokemon
        if choice == "1":
            print("You begin searching for Pokemon....\n")
            time.sleep(2)

            #TODO: Add choice if it's a pokemon you already have, and if you want to catch it again.
            #Pokemon found, choice to catch it. 
            found_pokemon = pokedex.find_pokemon()
            if found_pokemon is not None:
                print(f"You found a wild {found_pokemon.name.capitalize()}!\n")
                options = ["yes", "no", "y", "n"]
                max_attempts = 5
                attempts = 0
                ball_modifier = 1

                #Starting catching loop, attempts at 0, max at 5. 
                catching = True
                while catching:
                    if attempts >= max_attempts:
                        print(f"{found_pokemon.name.capitalize()} ran away!")
                        break

                    catch_choice = input("Would you like to catch it?: (Yes/No) ").strip().lower()

                    if catch_choice == "yes" or catch_choice == "y":
                        f = 4
                        catch_rate = pokedex.get_catch_rate(found_pokemon.dex)
                        probability = 1 + (((catch_rate + 1) * 255 + f + 1256) / (255 + 1))
                        print(f"\nYour base catch chance is {min(probability / 255, 1.0)*100:.2f}%")

                        #Choosing pokeball, and updating the modifier
                        choosing_ball = True
                        while choosing_ball:
                            ball_options = ["1", "2", "3"]
                            ball_choice = pokedex.pokeball_choice_prompt()

                            #Error handling for invalid input
                            if ball_choice not in ball_options:
                                print("Choose another option.")
                                continue
                            
                            ball_modifier = pokedex.get_pokeball_modifier(int(ball_choice))
                            probability = 1 + (((catch_rate + 1) * ball_modifier + f + 1256) / (ball_modifier + 1))
                            catch_percent = min(probability/255, 1.0)*100
                            break

                        #Calculating catch chance based on dex number, and ball modifier. Setting to 100% if exceeds 100.
                        probability = 1 + (((catch_rate + 1) * ball_modifier + f + 1256) / (ball_modifier + 1))
                        catch_percent = min(probability/255, 1.0)*100
                        print(f"\nYou have a {catch_percent:.2f}% chance to catch it!")
                        time.sleep(1)

                        #Catching Pokemon.
                        if catch_percent >= 100:
                            time.sleep(1)
                            pokedex.guarantee_catch(found_pokemon)
                            catching = False
                        else:
                            #Attempting to catch the Pokemon, and displaying the result.
                            catch_attempt = pokedex.catch_pokemon(found_pokemon, ball_modifier)
                            print("You throw a Pokeball....\n")
                            time.sleep(1)

                            #catch pokemon, display pokedex page, sort inventory by id, break.
                            if catch_attempt:
                                pokedex.inventory.append({
                                    "id": found_pokemon.dex,
                                    "name": found_pokemon.name
                                })
                                pokedex.display_pokemon(found_pokemon)
                                pokedex.inventory = sorted(pokedex.inventory, key=lambda x: x["id"])
                                catching = False
                            else:
                                print("Catch attempt Failed!\n")
                                attempts += 1
                                continue

                    elif catch_choice == "no" or catch_choice == "n":
                        print(f"You let the wild {found_pokemon.name.capitalize()} go!\n")
                        catching = False

                    else:
                        print("Invalid choice. Please try again.")
                        continue
            else:
                print("No Pokemon found.... try again!")
        #Pokedex Search
        if choice == "2":
            pokedex.start()

        #Looks at Pokemon inventory
        #TODO: Add option to remove Pokemon from inventory
        elif choice == "3":
            inventory = pokedex.get_inventory()

            if inventory is not None and len(inventory) > 0:
                print("\nYour Pokemon:")
                for poke in inventory:
                    print(f"[ID: {poke['id']}] {poke['name'].capitalize()}")
            else:
                print("You have no Pokemon in your inventory.")

        elif choice == "4":
            pokedex.shop_prompt()
        elif choice == "5":
            current_inventory = pokedex.get_inventory()

            #Save game check
            should_save = pokedex.has_changes(current_inventory)
            if should_save:
                pokedex.save_game_prompt()
            in_progress = False

    print("Until next time, trainer!")

if __name__ == "__main__":
    main()
