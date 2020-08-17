/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020  Erwan Grâce <erwan.grace@outlook.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file CommandLineParsingResult.h
 * @author Erwan
 * @date 01/11/2019
 */

#ifndef SIMPHONIZ_COMMANDLINEPARSINGRESULT_H
#define SIMPHONIZ_COMMANDLINEPARSINGRESULT_H

namespace simphoniz {

/**
 * @brief Defines the possible outcomes of the command-line parsing.
 * @ingroup console
 */
enum class CommandLineParsingResult {
    OK,               ///< The parsing succeeded.
    KO,               ///< The parsing failed.
    HELP_REQUESTED,   ///< The help option was present.
    VERSION_REQUESTED ///< The version option was present.
};

} // namespace simphoniz

#endif // SIMPHONIZ_COMMANDLINEPARSINGRESULT_H
