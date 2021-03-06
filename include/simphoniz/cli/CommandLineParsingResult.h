/* Simphoniz - A Simple Photo Organizer
 * Copyright (C) 2020, 2021  Erwan Grâce <erwan.grace@outlook.fr>
 *
 * This file is part of Simphoniz.
 *
 * Simphoniz is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Simphoniz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Simphoniz.  If not, see <https://www.gnu.org/licenses/>.
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
 * @ingroup cli
 */
enum class CommandLineParsingResult {
    kOk,              ///< The parsing succeeded.
    kKo,              ///< The parsing failed.
    kHelpRequested,   ///< The help option was present.
    kVersionRequested ///< The version option was present.
};

} // namespace simphoniz

#endif // SIMPHONIZ_COMMANDLINEPARSINGRESULT_H
